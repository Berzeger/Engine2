#pragma once

#include "Running/Renderer/RendererApi.h"

namespace Running
{
	class OpenGlRendererApi : public RendererApi
	{
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
