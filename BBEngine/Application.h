#pragma once
#include "Interface.h"

namespace BB
{
	struct Application : AppInterface
	{
		inline Application()
		{
			m_LayerID = TypeID<Application>();
			m_Context = new AppContext();
		}

		inline ~Application()
		{
			BB_DELETE(m_Context);
		}

		inline void RunContext()
		{
			while (true)
			{
				m_Context->Dispatcher.PollEvents();

				for (auto& layer : m_Context->Layers)
				{
					layer->OnUpdate();
				}
			}
		}
	};
}