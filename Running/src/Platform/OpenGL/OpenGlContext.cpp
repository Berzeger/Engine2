#include "pch.h"
#include "OpenGlContext.h"

namespace Running
{
	OpenGlContext::OpenGlContext(GLFWwindow* windowHandle)
		: _windowHandle(windowHandle)
	{
		RUNNING_CORE_ASSERT(_windowHandle, "Window handle is null!");
	}

	void OpenGlContext::Init()
	{
		glfwMakeContextCurrent(_windowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RUNNING_CORE_ASSERT(status, "Failed to initialize Glad!");

		RUNNING_CORE_INFO("OpenGL Info:");
		RUNNING_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		RUNNING_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		RUNNING_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGlContext::SwapBuffers()
	{
		glfwSwapBuffers(_windowHandle);
	}
}
