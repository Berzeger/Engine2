#pragma once
#include "Running/Core.h"
#include "Running/Log.h"
#include "Running/Window.h"
#include "Running/Events/ApplicationEvent.h"
#include "Running/Events/KeyEvent.h"
#include "Running/Events/MouseEvent.h"
#include "Running/LayerStack.h"

namespace Running
{
	class RUNNING_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_instance; }
		inline Window& GetWindow() { return *_window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> _window;
		bool _running = true;
		LayerStack _layerStack;
		static Application* s_instance;
	};

	// To be defined in client
	Application* CreateApplication();
}
