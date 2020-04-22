#include "pch.h"
#include "Application.h"
#include "Input.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Running
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		RUNNING_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback([&](Event& e)
		{
			OnEvent(e);
		});

		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent& event)
		{
			return OnWindowClose(event);
		});

		for (auto it = _layerStack.end(); it != _layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}

		RUNNING_CORE_TRACE("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}

	void Application::Run()
	{
		while (_running)
		{
			float time = (float)glfwGetTime(); // todo: Platform::GetTime(), don't depend on GLFW
			Timestep dt = time - _lastFrameTime;
			_lastFrameTime = time;

			for (Layer* layer : _layerStack)
			{
				layer->OnUpdate(dt);
			}

			_imGuiLayer->Begin();
			for (Layer* layer : _layerStack)
			{
				layer->OnImGuiRender();
			}
			_imGuiLayer->End();

			_window->OnUpdate();
		}
	}
}
