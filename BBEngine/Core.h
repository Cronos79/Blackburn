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