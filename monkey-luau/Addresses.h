#pragma once
#include <Windows.h>
#include <cstdint>

const std::uintptr_t current_module = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));

namespace func_defs
{
	using rbx_print_t = void(__fastcall*)(std::int16_t output_type, const char* str);
	using rbx_spawn_t = int(__cdecl*)(std::uintptr_t rl, ...);
}

namespace rbx {
	func_defs::rbx_print_t print = (func_defs::rbx_print_t)(addresses::rbx_output_addy);
	func_defs::rbx_spawn_t spawn = (func_defs::rbx_spawn_t)(addresses::spawn_func_addy);
}

namespace addresses
{
	const std::uintptr_t rbx_output_addy = current_module + 0x2CFE80;

	const std::uintptr_t spawn_func_addy = current_module + 0x492A30;
	const std::uintptr_t deserializer_func_addy = current_module + 0x147C4A0;
}

namespace offsets
{

	namespace job
	{
		constexpr std::uintptr_t name = 0x10;
	}

	namespace waiting_scripts_job
	{
		constexpr std::uintptr_t datamodel = 0x28;
		constexpr std::uintptr_t script_context = 0x130;
	}

	namespace luastate
	{
		constexpr std::uintptr_t state = 0x0;
	}
}