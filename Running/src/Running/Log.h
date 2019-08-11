#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Running
{
	class RUNNING_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
	};
}

// Core log macros
#define RUNNING_CORE_CRITICAL(...) Running::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define RUNNING_CORE_ERROR(...) Running::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RUNNING_CORE_WARN(...) Running::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RUNNING_CORE_INFO(...) Running::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RUNNING_CORE_TRACE(...) Running::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define RUNNING_CLIENT_CRITICAL(...) Running::Log::GetClientLogger()->critical(__VA_ARGS__)
#define RUNNING_CLIENT_ERROR(...) Running::Log::GetClientLogger()->error(__VA_ARGS__)
#define RUNNING_CLIENT_WARN(...) Running::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RUNNING_CLIENT_INFO(...) Running::Log::GetClientLogger()->info(__VA_ARGS__)
#define RUNNING_CLIENT_TRACE(...) Running::Log::GetClientLogger()->trace(__VA_ARGS__)
