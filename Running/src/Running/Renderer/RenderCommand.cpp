#include "pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGlRendererApi.h"

namespace Running
{
	RendererApi* RenderCommand::s_rendererApi = new OpenGlRendererApi;
}
