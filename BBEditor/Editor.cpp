#include <BlackBurn.h>

using namespace BB;

struct TestEvent
{
	uint32_t Data = 0;
};

struct MyLayer : AppInterface
{
	inline void OnAttach()
	{		
		AttachCallback<TestEvent>([this](auto event)
			{
				BB_TRACE("On start");
				DetachLayer<MyLayer>();
			});
	}

	inline void OnUpdate()
	{
		if (++m_Counter == 10)
		{
			PostEvent<TestEvent>();
		}
	}

	int m_Counter = 0;
};

int32_t main(int32_t argc, char** argv)
{
	BB::BBLog::Init();
	auto app = new Application();
	app->AttachLayer<MyLayer>();
	app->RunContext();
	return 0;
}