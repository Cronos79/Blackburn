#pragma once

#include <queue>
#include <vector>
#include <string>
#include <bitset>
#include <memory>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <stdint.h>

// import export
#if BB_EXPORT
#define BB_API __declspec(dllexport)
#else
#define BB_API __declspec(dllimport)
#endif


// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma warning(pop)



namespace BB {	
	class BBLog
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	std::shared_ptr<spdlog::logger> BBLog::s_ClientLogger;

	void BBLog::Init()
	{
		spdlog::set_pattern("%^[%T] %@ %n: %v%$");
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}

// Client log macros
#ifdef BB_DEBUG
#define BB_TRACE(...)         ::BB::BBLog::GetClientLogger()->trace(__VA_ARGS__)
#define BB_INFO(...)          ::BB::BBLog::GetClientLogger()->info(__VA_ARGS__)
#define BB_WARN(...)          ::BB::BBLog::GetClientLogger()->warn(__VA_ARGS__)
#define BB_ERROR(...)         ::BB::BBLog::GetClientLogger()->error(__VA_ARGS__)
#define BB_CRITICAL(...)      ::BB::BBLog::GetClientLogger()->critical(__VA_ARGS__)
#else
#define BB_TRACE
#define BB_INFO
#define BB_WARN
#define BB_ERROR
#define BB_CRITICAL
#endif

// type id
namespace BB
{
	template<typename T>
	inline constexpr uint32_t TypeID()
	{
		return static_cast<uint32_t>(reinterpret_cast<std::uintptr_t>(&typeid(T)));
	}
}

// free memory
#define BB_DELETE(ptr) if(ptr != nullptr) { delete(ptr); ptr = nullptr; }