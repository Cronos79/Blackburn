#pragma once
#include "Core.h"

namespace BB
{
	struct AppInterface;

	struct AppContext
	{
		inline ~AppContext()
		{
			for (auto& layer : Layers)
			{
				BB_DELETE(layer);
			}
		}

		std::vector<AppInterface*> Layers;
	};
}