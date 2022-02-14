#include "interfaces.h"
#include <iostream>

typedef void* (__cdecl* t_CreateInterface)(const char*, int*);

void* interfaces::get_interface(const char* module, const char* name) {
	auto dll = GetModuleHandleA(module);
	if (!dll) return nullptr;
	// köszönjük az exportált functiont a dll-nek
	auto CreateInterface = reinterpret_cast<t_CreateInterface>(GetProcAddress(dll, "CreateInterface"));
	int return_code;
	return CreateInterface(name, &return_code);
}
