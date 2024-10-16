#include <BlackBurn.h>
#include "BBLog.h"
//#include "BBGameObject.h"
#include "Scene.h"

using namespace BB;

int32_t main(int32_t argc, char** argv)
{
	BB::BBLog::Init();
	auto* app = new Application(1920,1080,"Blackburn Editor");

	TestScene* ts = new TestScene(app);
	
	app->RunContext();
	return 0;
}