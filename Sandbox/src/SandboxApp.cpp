#pragma once

#include <Running.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Running::Layer
{
public:
	ExampleLayer() :
		Layer("Example"),
		_camera(-1.6f, 1.6f, -0.9f, 0.9f),
		_cameraPosition(0.0f),
		_squarePosition(0.0f)
	{
		// triangle
		_triangleVertexArray = Running::VertexArray::Create();

		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Running::VertexBuffer> triangleVertexBuffer = Running::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));

		Running::BufferLayout layout = {
			{ "a_Position", Running::ShaderDataType::Float3 },
			{ "a_Color", Running::ShaderDataType::Float4 }
		};

		triangleVertexBuffer->SetLayout(layout);
		_triangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Running::IndexBuffer> triangleIndexBuffer = Running::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		_triangleVertexArray->SetIndexBuffer(triangleIndexBuffer);

		// square
		_squareVertexArray = Running::VertexArray::Create();

		float squareVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Running::VertexBuffer> squareVertexBuffer = Running::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		Running::BufferLayout squareLayout = {
			{ "a_Position", Running::ShaderDataType::Float3 }
		};

		squareVertexBuffer->SetLayout(squareLayout);
		_squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 0, 3, 2 };
		std::shared_ptr<Running::IndexBuffer> squareIndexBuffer = Running::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		_squareVertexArray->SetIndexBuffer(squareIndexBuffer);

		// shaders

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() 
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
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

		std::string blueVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main() 
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() 
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		_shader.reset(Running::Shader::Create(vertexSrc, fragmentSrc));
		_blueShader.reset(Running::Shader::Create(blueVertexSrc, blueFragmentSrc));
	}

	void OnUpdate(Running::Timestep dt) override
	{
		//RUNNING_CLIENT_TRACE("Delta time: {0}s ({1}ms)", dt.GetSeconds(), dt.GetMilliseconds());

		if (Running::Input::IsKeyPressed(RUNNING_KEY_LEFT))
		{
			_cameraPosition.x -= _cameraMoveSpeed * dt;
		}
		else if (Running::Input::IsKeyPressed(RUNNING_KEY_RIGHT))
		{
			_cameraPosition.x += _cameraMoveSpeed * dt;
		}

		if (Running::Input::IsKeyPressed(RUNNING_KEY_DOWN))
		{
			_cameraPosition.y -= _cameraMoveSpeed * dt;
		}
		else if (Running::Input::IsKeyPressed(RUNNING_KEY_UP))
		{
			_cameraPosition.y += _cameraMoveSpeed * dt;
		}

		if (Running::Input::IsKeyPressed(RUNNING_KEY_A))
		{
			_cameraRotation += _cameraRotationSpeed * dt;
		}
		else if (Running::Input::IsKeyPressed(RUNNING_KEY_D))
		{
			_cameraRotation -= _cameraRotationSpeed * dt;
		}

		if (Running::Input::IsKeyPressed(RUNNING_KEY_J))
		{
			_squarePosition.x -= _squareMoveSpeed * dt;
		}
		else if (Running::Input::IsKeyPressed(RUNNING_KEY_L))
		{
			_squarePosition.x += _squareMoveSpeed * dt;
		}

		if (Running::Input::IsKeyPressed(RUNNING_KEY_I))
		{
			_squarePosition.y += _squareMoveSpeed * dt;
		}
		else if (Running::Input::IsKeyPressed(RUNNING_KEY_K))
		{
			_squarePosition.y -= _squareMoveSpeed * dt;
		}

		Running::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Running::RenderCommand::Clear();

		_camera.SetPosition(_cameraPosition);
		_camera.SetRotation(_cameraRotation);

		Running::Renderer::BeginScene(_camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(0.1f));

		for (int x = 0; x < 20; ++x)
		{
			for (int y = 0; y < 20; ++y)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Running::Renderer::Submit(_blueShader, _squareVertexArray, transform);
			}
		}

		//Running::Renderer::Submit(_blueShader, _squareVertexArray, transform);
		//Running::Renderer::Submit(_shader, _triangleVertexArray);

		Running::Renderer::EndScene();
	}

private:
	std::shared_ptr<Running::Shader> _shader;
	std::shared_ptr<Running::Shader> _blueShader;
	std::shared_ptr<Running::VertexArray> _triangleVertexArray;
	std::shared_ptr<Running::VertexArray> _squareVertexArray;

	Running::OrthographicCamera _camera;
	glm::vec3 _cameraPosition;
	float _cameraMoveSpeed = 10.0f;

	float _cameraRotation = 0.0f;
	float _cameraRotationSpeed = 200.0f;

	glm::vec3 _squarePosition;
	float _squareMoveSpeed = 10.0f;
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
