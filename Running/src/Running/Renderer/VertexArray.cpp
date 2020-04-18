#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGlVertexArray.h"

namespace Running {

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::None:
			RUNNING_CORE_ASSERT(false, "RendererApi::None is currently not supported!");
			return nullptr;

		case RendererApi::OpenGL:
			std::shared_ptr<VertexArray> openGlVertexArray;
			openGlVertexArray.reset(new OpenGlVertexArray());
			return openGlVertexArray;
		}

		RUNNING_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}
}
