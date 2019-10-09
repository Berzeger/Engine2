#pragma once

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

#ifdef RUNNING_PLATFORM_WINDOWS

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
	#error Running Engine only supports Windows!
#endif
