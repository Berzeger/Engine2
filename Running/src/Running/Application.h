#pragma once
#include "Running/Core.h"
#include "Running/Window.h"

#include "Running/Events/ApplicationEvent.h"
#include "Running/LayerStack.h"

#include "Running/ImGui/ImGuiLayer.h"

namespace Running
{
	class Application
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
		ImGuiLayer* _imGuiLayer;
		bool _running = true;
		LayerStack _layerStack;

		static Application* s_instance;
	};

	// To be defined in client
	Application* CreateApplication();
}
