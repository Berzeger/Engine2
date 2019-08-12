#include "Application.h"
#include "Events/ApplicationEvent.h"

#include <iostream>

namespace Running
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1024, 768);
		RUNNING_CLIENT_TRACE(e);
		while (true);
	}
}