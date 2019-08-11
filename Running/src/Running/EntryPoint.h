#pragma once

#ifdef RUNNING_PLATFORM_WINDOWS
#include "Running.h"

extern Running::Application* Running::CreateApplication();

int main(int argc, char ** argv)
{
	Running::Log::Init();
	RUNNING_CORE_WARN("Initialized the logging subsystem");
	RUNNING_CLIENT_INFO("Hi!");
	
	Running::Application* app = Running::CreateApplication();
	app->Run();
	delete app;
}
#else
	#error Running only supports Windows!
#endif
