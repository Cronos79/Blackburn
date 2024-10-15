#pragma once
#include "Core.h"
#include "Event.h"

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

		EventDispatcher Dispatcher;
	};
}