#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
#include "Engine.h"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char ** argv)
{
	Engine::Application* app = Engine::CreateApplication();
	app->Run();
	delete app;
}
#else
	#error Engine only supports Windows!
#endif
