#include "pch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGlBuffer.h"

namespace Running
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::None:
				RUNNING_CORE_ASSERT(false, "RendererApi::None is currently not supported!");
				return nullptr;
					
			case RendererApi::OpenGL:
				return new OpenGlVertexBuffer(vertices, size);
		}

		RUNNING_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::None:
				RUNNING_CORE_ASSERT(false, "RendererApi::None is currently not supported!");
				return nullptr;

			case RendererApi::OpenGL:
				return new OpenGlIndexBuffer(indices, size);
		}

		RUNNING_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}
}
