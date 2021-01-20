#include "ExampleLayer.h"
#include "imgui.h"
#include "Platform/OpenGL/OpenGlShader.h"
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer() :
	Layer("Example"),
	_camera(-1.6f, 1.6f, -0.9f, 0.9f),
	_cameraPosition(0.0f),
	_squarePosition(0.0f),
	_redSquareColor(0.8f, 0.2f, 0.2f, 1.0f),
	_blueSquareColor(0.2f, 0.2f, 0.8f, 1.0f)
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

	std::string flatColorVertexSrc = R"(
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

	std::string flatColorFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			uniform vec4 u_Color;

			void main() 
			{
				color = u_Color;
			}
		)";

	_shader.reset(Running::Shader::Create(vertexSrc, fragmentSrc));
	_flatColorShader.reset(Running::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc));
}

void ExampleLayer::OnUpdate(Running::Timestep dt)
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
	glm::vec4 redColor(0.8f, 0.2f, 0.2f, 1.0f);
	glm::vec4 blueColor(0.2f, 0.2f, 0.8f, 1.0f);

	std::dynamic_pointer_cast<Running::OpenGlShader>(_flatColorShader)->Bind();

	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			if (y % 2 == 0)
			{
				std::dynamic_pointer_cast<Running::OpenGlShader>(_flatColorShader)->UploadUniformFloat4("u_Color", _redSquareColor);
			}
			else
			{
				std::dynamic_pointer_cast<Running::OpenGlShader>(_flatColorShader)->UploadUniformFloat4("u_Color", _blueSquareColor);
			}
			Running::Renderer::Submit(_flatColorShader, _squareVertexArray, transform);
		}
	}

	//Running::Renderer::Submit(_blueShader, _squareVertexArray, transform);
	Running::Renderer::Submit(_shader, _triangleVertexArray);

	Running::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Red Square Color", glm::value_ptr(_redSquareColor));
	ImGui::ColorEdit3("Blue Square Color", glm::value_ptr(_blueSquareColor));
	ImGui::End();
}
