#pragma once

#include <Running.h>

class ExampleLayer : public Running::Layer
{
public:
	ExampleLayer() : 
		Layer("Example"),
		_camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		_vertexArray = Running::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Running::VertexBuffer> vertexBuffer = Running::VertexBuffer::Create(vertices, sizeof(vertices));

		Running::BufferLayout layout = {
			{ "a_Position", Running::ShaderDataType::Float3 },
			{ "a_Color", Running::ShaderDataType::Float4 }
		};

		vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Running::IndexBuffer> indexBuffer = Running::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		_vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() 
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);	
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

		_shader.reset(Running::Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override
	{
		Running::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Running::RenderCommand::Clear();

		_camera.SetRotation(45.0f);

		Running::Renderer::BeginScene(_camera);

		Running::Renderer::Submit(_shader, _vertexArray);

		Running::Renderer::EndScene();
	}

private:
	std::shared_ptr<Running::Shader> _shader;
	std::shared_ptr<Running::VertexArray> _vertexArray;

	Running::OrthographicCamera _camera;
};

class Sandbox : public Running::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Running::Application* Running::CreateApplication()
{
	return new Sandbox();
}
