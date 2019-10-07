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
	}

	void OpenGlContext::SwapBuffers()
	{
		glfwSwapBuffers(_windowHandle);
	}
}
