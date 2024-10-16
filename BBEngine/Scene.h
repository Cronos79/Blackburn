#pragma once
#include "Core.h"
#include "BBGameObject.h"
#include "Interface.h"
#include "BBWindow.h"

namespace BB
{
	struct TestEvent
	{
		uint32_t Data = 0;
	};

	struct MyLayer : BBGameObject
	{
	protected:
		inline void OnAttach() override
		{
			SetName("MyLayer");
			AttachCallback<TestEvent>([this](auto event)
				{					
					BB_TRACE("On start");
					DetachLayer<MyLayer>();
				});
		}

		inline void OnUpdate() override
		{
			if (++m_Counter == 10)
			{
				PostEvent<TestEvent>();
			}
		}

		inline void OnDetach() override
		{
			BB_ERROR("Detach");
		}

		int m_Counter = 0;
	private:
		friend struct AppInterface;
	};

	struct Scene
	{
		Scene(Application* app)
		{
			m_App = app;
		}
	protected:
		Application* m_App;
	};

	struct TestScene : Scene
	{
		TestScene(Application* app)
			: Scene(app)
		{
			m_App->AttachLayer<MyLayer>();
		}
		
	};
}