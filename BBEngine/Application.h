#pragma once
#include "Interface.h"
#include "BBWindow.h"

namespace BB
{
	struct Application : AppInterface
	{
		inline Application(int32_t width,int32_t height,std::string title)
			: wnd(width, height, title.c_str())
		{
			m_LayerID = TypeID<Application>();
			m_Context = new AppContext();
		}

		inline ~Application()
		{
			BB_DELETE(m_Context);
		}

		inline int RunContext()
		{
			while (true)
			{
				// process all messages pending, but to not block for new messages
				if (const auto ecode = BBWindow::ProcessMessages())
				{
					// if return optional has value, means we're quitting so return exit code
					return *ecode;
				}
				// execute the game logic
				//const auto dt = timer.Mark() * speed_factor;

				m_Context->Dispatcher.PollEvents();

				for (auto& layer : m_Context->Layers)
				{
					layer->OnUpdate();
				}
			}
		}

	private:
		std::string commandLine;
		BBWindow wnd;
	};
}