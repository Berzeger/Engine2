#include "pch.h"
#include "Application.h"
#include <glad/glad.h>
#include "Input.h"

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

		// Vertex array
		// Vertex buffer
		// Index buffer
		glGenVertexArrays(1, &_vertexArray);
		glBindVertexArray(_vertexArray);
		
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[3] = { 0, 1, 2 };
		_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main() 
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() 
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);	
			}
		)";

		_shader.reset(Shader::Create(vertexSrc, fragmentSrc));
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			_shader->Bind();
			glBindVertexArray(_vertexArray);
			glDrawElements(GL_TRIANGLES, _indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : _layerStack)
			{
				layer->OnUpdate();
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
