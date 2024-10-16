#pragma once
#include "Core.h"

namespace BB
{
	struct BBObject
	{
		inline void SetName(std::string name) { m_Name = name; }
		inline std::string GetName() { return m_Name; }
	private:
		std::string m_Name;
	};
}