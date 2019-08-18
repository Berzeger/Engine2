#pragma once
#include "Core.h"
#include "Log.h"
#include "Window.h"

namespace Running
{
	class RUNNING_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		
	private:
		std::unique_ptr<Window> _window;
		bool _running = true;
	};

	// To be defined in client
	Application* CreateApplication();
}