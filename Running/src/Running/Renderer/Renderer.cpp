#include "pch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGlShader.h"

namespace Running
{
	Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_sceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGlShader>(shader)->UploadUniformMat4("u_ViewProjectionMatrix", s_sceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGlShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
