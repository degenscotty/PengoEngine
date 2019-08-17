#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

// Core Log Macros
#define CORE_TRACE(...)	::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define CORE_INFO(...)	::Log::GetCoreLogger()->info(__VA_ARGS__);
#define CORE_WARN(...)	::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define CORE_ERROR(...)	::Log::GetCoreLogger()->error(__VA_ARGS__);
#define CORE_FATAL(...)	::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// Client Log Macros		
#define CLIENT_TRACE(...)		::Log::GetClientLogger()->trace(__VA_ARGS__);
#define CLIENT_INFO(...)		::Log::GetClientLogger()->info(__VA_ARGS__);
#define CLIENT_WARN(...)		::Log::GetClientLogger()->warn(__VA_ARGS__);
#define CLIENT_ERROR(...)		::Log::GetClientLogger()->error(__VA_ARGS__);
#define CLIENT_FATAL(...)		::Log::GetClientLogger()->fatal(__VA_ARGS__);

#define ASSERT(x, ...) { if(!(x)) { CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define CORE_ASSERT(x, ...) { if(!(x)) { CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

