#include <iostream>
#include <windows.h>
#include <thread>
#include "interfaces.h"
#include "global.h"
#include "QAngle.h"

using namespace std::chrono_literals;

FILE* console_dummy;
void create_console(const char* title) {
	AllocConsole();
	freopen_s(&console_dummy, "CONOUT$", "w", stdout); // a CONOUT$ "fájlba" reassignolja az stdout streamet, reopeneli hogy abba menjen
	SetConsoleTitleA(title);
}

void destroy_console() {
	fclose(console_dummy);
	FreeConsole();
	DestroyWindow(GetConsoleWindow());
}

void __stdcall entry_thread(HMODULE module) {
	while (!GetModuleHandleA("serverbrowser.dll")) { // megvárjuk, amíg a játék eljut a menübe, ott loadolódik be a serverbrowser.dll
		std::this_thread::sleep_for(200ms);
	}

	create_console("Karesz Klub"); // lefoglaljuk a console-t

	// lekéregetjük a szükséges dolgokat a csgo-ból
	global::module = module;
	global::client_dll = GetModuleHandleA("client.dll");
	global::engine_dll = GetModuleHandleA("engine.dll");
	interfaces::client_state = reinterpret_cast<IEngineClient*>(interfaces::get_interface("engine.dll", "VEngineClient014"));
	interfaces::entity_list = reinterpret_cast<IClientEntityList*>(interfaces::get_interface("client.dll", "VClientEntityList003"));

	while (!GetAsyncKeyState(VK_DELETE)) {

		if (interfaces::client_state->is_in_game()) {
			auto max_clients = interfaces::client_state->get_max_clients();
			global::local_player = reinterpret_cast<LocalPlayer*>(interfaces::entity_list->get_client_entity(interfaces::client_state->get_local_player_index()));

			float lowest_delta = FLT_MAX;
			QAngle lowest_delta_angle;

			// végigmegyün	k az összes playeren
			for (int i = 1; i <= max_clients; i++)
			{
				if (i == interfaces::client_state->get_local_player_index()) continue;
				auto ent = interfaces::entity_list->get_client_entity(i);
				if (!ent || ent->is_dormant || !ent->is_alive() || ent->team == global::local_player->team) continue; // egy pár check

				// jelenjen meg a radaron
				ent->spotted = true;

				// aimbot
				// megkeressük a nézethez legközelebbi playert (igen, el kell végezni mindenkin a calcangle-t)
				auto angle = QAngle::calc_angle(global::local_player->get_eye_position(), ent->get_eye_position());
				auto delta = (angle - global::local_player->get_view_angles()).length_2d();
				if (delta < lowest_delta) {
					lowest_delta = delta;
					lowest_delta_angle = angle;
				}

			}

			if (GetAsyncKeyState(VK_LMENU) && lowest_delta != FLT_MAX) {
				global::local_player->set_view_angles(lowest_delta_angle);
			}

			/*if (GetAsyncKeyState(VK_SPACE)) // elvileg a bunnyhop, de nem működik a memóriaírás valamiért
			{
				if (global::local_player->flags & (int)flag_t::on_ground) {
					*(reinterpret_cast<std::uint32_t*>(GetModuleHandleA("client.dll") + 0x52789F8)) = 6;
				}
				else {
					*(reinterpret_cast<std::uint32_t*>(GetModuleHandleA("client.dll") + 0x52789F8)) = 4;
				}
			}*/
		}
		std::this_thread::sleep_for(1ms);
	}

	destroy_console();
	FreeLibraryAndExitThread(module, EXIT_SUCCESS); // ez unloadolja a dll-ünket a csgo-ból, 0 exit kóddal
}

bool __stdcall DllMain(HMODULE module, DWORD reason, void* reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(module); // ha a csgo új threadet csinál, meghívná újra azzal a threaddel a beloadolt dll-ek entry pointját, ezt is. ezt kikapcsoljuk

		if (!GetModuleHandleA("csgo.exe")) return false; // ha nem a csgo loadolta be, akkor rögtön lépjünk ki

		if (auto thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)entry_thread, module, 0, 0))
			CloseHandle(thread);

		return true;
	}
	return false;
}