#pragma once

#include "Running/Renderer/GraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace Running
{
	class OpenGlContext : public GraphicsContext
	{
	public:
		OpenGlContext(GLFWwindow* windowHandle);
		
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* _windowHandle;
	};
}
