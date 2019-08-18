project "GLFW"
	kind "StaticLib"
	language "C"

	location("../../vendor/GLFW")

	targetdir ("../../vendor/GLFW/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../../vendor/GLFW/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"../../vendor/GLFW/include/GLFW/glfw3.h",
		"../../vendor/GLFW/include/GLFW/glfw3native.h",
		"../../vendor/GLFW/src/glfw_config.h",
		"../../vendor/GLFW/src/context.c",
		"../../vendor/GLFW/src/init.c",
		"../../vendor/GLFW/src/input.c",
		"../../vendor/GLFW/src/monitor.c",
		"../../vendor/GLFW/src/vulkan.c",
		"../../vendor/GLFW/src/window.c"
	}
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"../../vendor/GLFW/src/x11_init.c",
			"../../vendor/GLFW/src/x11_monitor.c",
			"../../vendor/GLFW/src/x11_window.c",
			"../../vendor/GLFW/src/xkb_unicode.c",
			"../../vendor/GLFW/src/posix_time.c",
			"../../vendor/GLFW/src/posix_thread.c",
			"../../vendor/GLFW/src/glx_context.c",
			"../../vendor/GLFW/src/egl_context.c",
			"../../vendor/GLFW/src/osmesa_context.c",
			"../../vendor/GLFW/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		buildoptions { "-std=c++11", "-lgdi32" }

		systemversion "latest"
		staticruntime "On"

		files
		{
			"../../vendor/GLFW/src/win32_init.c",
			"../../vendor/GLFW/src/win32_joystick.c",
			"../../vendor/GLFW/src/win32_monitor.c",
			"../../vendor/GLFW/src/win32_time.c",
			"../../vendor/GLFW/src/win32_thread.c",
			"../../vendor/GLFW/src/win32_window.c",
			"../../vendor/GLFW/src/wgl_context.c",
			"../../vendor/GLFW/src/egl_context.c",
			"../../vendor/GLFW/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
