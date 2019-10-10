#pragma once
#include "Running/Core.h"
#include "Running/Log.h"
#include "Running/Window.h"
#include "Running/Events/ApplicationEvent.h"
#include "Running/Events/KeyEvent.h"
#include "Running/Events/MouseEvent.h"
#include "Running/LayerStack.h"

#include "Running/ImGui/ImGuiLayer.h"
#include "Running/Renderer/Shader.h"

#include "Running/Renderer/Buffer.h"

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

		unsigned int _vertexArray;
		std::unique_ptr<Shader> _shader;
		std::unique_ptr<VertexBuffer> _vertexBuffer;
		std::unique_ptr<IndexBuffer> _indexBuffer;

		static Application* s_instance;
	};

	// To be defined in client
	Application* CreateApplication();
}
