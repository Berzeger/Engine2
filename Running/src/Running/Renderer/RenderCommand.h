#pragma once

#include "RendererApi.h"

namespace Running
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_rendererApi->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_rendererApi->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_rendererApi->DrawIndexed(vertexArray);
		}

	private:
		static RendererApi* s_rendererApi;
	};
}
