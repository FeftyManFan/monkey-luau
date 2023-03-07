#include <stack>
#include <mutex>
#include <iostream>

#include "Addresses.h"


std::mutex mutex;
std::stack<std::string> script_queue;
std::uintptr_t original_func;

struct roblox_encoder_t {
	std::uint8_t roblox_encoder_t::encodeOp(const std::uint8_t opcode)
	{
		return opcode * 227;
	}
};

int __fastcall scheduler_cycle(std::uintptr_t waiting_scripts_job, int fakearg, int a2)
{

	std::unique_lock<std::mutex> guard{ mutex };
	std::uintptr_t rl = 0;

	if (!script_queue.empty())
	{
		const std::string bytecode = script_queue.top();
		script_queue.pop();
		guard.unlock();


		if (bytecode.at(0) == 0)
		{
			rbx::print(1, "Script Error");
		}
		else
		{
			//rbx::deserialize(rl, "monkey", bytecode.c_str(), bytecode.size());
			rbx::spawn(rl);
			//rbx_decrement_top(rl, 1);
		}
	}

	return reinterpret_cast<int(__thiscall*)(std::uintptr_t, int)>(original_func)(waiting_scripts_job, a2);
}

namespace execution {

	void execution::run_script(const std::string& script)
	{
		roblox_encoder_t roblox_encoder{};
		const std::string& compiled = Luau::compile(script, {}, {}, &roblox_encoder); // no clone here, is gonna be cloned on queue
		std::unique_lock<std::mutex> guard{ mutex };
		script_queue.push(compiled);
	}

	void execution::run_bytecode(const std::string& bytecode)
	{
		std::unique_lock<std::mutex> guard{ mutex };
		script_queue.push(bytecode);
	}
}