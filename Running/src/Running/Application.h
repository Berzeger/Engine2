#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Log.h"

namespace Running
{
	class RUNNING_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}