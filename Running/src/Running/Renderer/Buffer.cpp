#include "pch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGlBuffer.h"

namespace Running
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::None:
				RUNNING_CORE_ASSERT(false, "RendererApi::None is currently not supported!");
				return nullptr;
					
			case RendererApi::OpenGL:
				std::shared_ptr<VertexBuffer> openGlVertexBuffer;
				openGlVertexBuffer.reset(new OpenGlVertexBuffer(vertices, size));
				return openGlVertexBuffer;
		}

		RUNNING_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::None:
				RUNNING_CORE_ASSERT(false, "RendererApi::None is currently not supported!");
				return nullptr;

			case RendererApi::OpenGL:
				std::shared_ptr<IndexBuffer> openGlIndexBuffer;
				openGlIndexBuffer.reset(new OpenGlIndexBuffer(indices, size));
				return openGlIndexBuffer;
		}

		RUNNING_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}
}
