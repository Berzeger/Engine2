#include "pch.h"
#include "Shader.h"
#include "Running/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlShader.h"

#include <glad/glad.h>

namespace Running
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetApi())
		{
			case RendererApi::None:
				RUNNING_CORE_ASSERT(false, "RendererApi::None is currently not supported!");
				return nullptr;

			case RendererApi::OpenGL:
				return new OpenGlShader(vertexSrc, fragmentSrc);
		}

		RUNNING_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}
}
