#include "pch.h"
#include "Application.h"
#include <glad/glad.h>
#include "Input.h"

namespace Running
{
	Application* Application::s_instance = nullptr;

	static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Running::ShaderDataType::Float:
			case Running::ShaderDataType::Float2:
			case Running::ShaderDataType::Float3:
			case Running::ShaderDataType::Float4:
			case Running::ShaderDataType::Mat3:
			case Running::ShaderDataType::Mat4:
				return GL_FLOAT;
			case Running::ShaderDataType::Int:
			case Running::ShaderDataType::Int2:
			case Running::ShaderDataType::Int3:
			case Running::ShaderDataType::Int4:
				return GL_INT;
			case Running::ShaderDataType::Bool:
				return GL_BOOL;
		}

		return 0;
	}

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
		
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ "a_Position", ShaderDataType::Float3 },
				{ "a_Color", ShaderDataType::Float4 }
			};

			_vertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const BufferLayout& layout = _vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
								  element.GetComponentCount(),
								  ShaderDataTypeToOpenGlBaseType(element.Type), 
								  element.Normalized ? GL_TRUE : GL_FALSE,
								  layout.GetStride(),
								  (const void*)element.Offset);
			index++;
		}


		uint32_t indices[3] = { 0, 1, 2 };
		_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() 
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() 
			{
				color = v_Color;
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
