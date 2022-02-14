#pragma once
#include <windows.h>
#include "entities.h"

inline namespace global {
	inline HMODULE module;
	inline HMODULE client_dll;
	inline HMODULE engine_dll;
	inline LocalPlayer* local_player;
}