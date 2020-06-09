#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Sesame {
	class SESAME_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


//Core log macros
#define SSM_CORE_TRACE(...) ::Sesame::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SSM_CORE_INFO(...) ::Sesame::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SSM_CORE_WARN(...) ::Sesame::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SSM_CORE_ERROR(...) ::Sesame::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SSM_CORE_FATAL(...) ::Sesame::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define SSM_TRACE(...) ::Sesame::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SSM_INFO(...) ::Sesame::Log::GetClientLogger()->info(__VA_ARGS__)
#define SSM_WARN(...) ::Sesame::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SSM_ERROR(...) ::Sesame::Log::GetClientLogger()->error(__VA_ARGS__)
#define SSM_FATAL(...) ::Sesame::Log::GetClientLogger()->critical(__VA_ARGS__)