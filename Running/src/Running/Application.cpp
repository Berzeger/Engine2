#include "pch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

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

		KeyPressedEvent kpe(30, 0);
		RUNNING_CLIENT_TRACE(kpe);

		MouseButtonReleasedEvent mbre(1);
		RUNNING_CLIENT_TRACE(mbre);
		while (true);
	}
}