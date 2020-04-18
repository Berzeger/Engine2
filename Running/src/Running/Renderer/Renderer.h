#pragma once

#include "RenderCommand.h"

namespace Running
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererApi::Api GetApi() { return RendererApi::GetApi(); }
	};
}
