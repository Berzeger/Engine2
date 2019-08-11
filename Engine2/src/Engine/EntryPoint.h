#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
#include "Engine.h"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char ** argv)
{
	Engine::Log::Init();
	ENGINE_CORE_WARN("Initialized the logging subsystem");
	ENGINE_CLIENT_INFO("Hi!");
	
	Engine::Application* app = Engine::CreateApplication();
	app->Run();
	delete app;
}
#else
	#error Engine only supports Windows!
#endif
