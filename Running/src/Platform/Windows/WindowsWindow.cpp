#include "pch.h"
#include "WindowsWindow.h"

#include "Running/Events/ApplicationEvent.h"
#include "Running/Events/KeyEvent.h"
#include "Running/Events/MouseEvent.h"

#include "Running/Renderer/GraphicsContext.h"
#include "Platform/OpenGL/OpenGlContext.h"

namespace Running
{
	static bool s_glfwInitialized = false;

	static void GLFWErrorCallback(int errorCode, const char* description)
	{
		RUNNING_CORE_ERROR("GLFW error ({0}): {1}", errorCode, description);
	}

	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		_data.Title = props.Title;
		_data.Width = props.Width;
		_data.Height = props.Height;

		RUNNING_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_glfwInitialized)
		{
			int success = glfwInit();
			RUNNING_CORE_ASSERT(success, "Failed to initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_glfwInitialized = true;
		}

		_window = glfwCreateWindow((int)props.Width, (int)props.Height, _data.Title.c_str(), nullptr, nullptr);
		_context = new OpenGlContext(_window);
		_context->Init();

		glfwSetWindowUserPointer(_window, &_data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
					}
				}
		});

		glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned codepoint) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(codepoint);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)x, (float)y);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		_context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		_data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return _data.VSync;
	}
}
