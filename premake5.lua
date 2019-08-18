workspace "RunningEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	startproject "Sandbox"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
IncludeDir = {}
IncludeDir["GLFW"] = "Running/vendor/GLFW"

include "Running/premakes/GLFW"
	
project "Running"
	location "Running"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Running/src/pch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}/include"
	}
	
	links 
	{
		"GLFW",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"RUNNING_PLATFORM_WINDOWS",
			"RUNNING_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
		
	filter "configurations:Debug" 
		defines 
		{
			"RUNNING_DEBUG",
			"RUNNING_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release" 
		defines "RUNNING_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist" 
		defines "RUNNING_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Running/vendor/spdlog/include",
		"Running/src"
	}
	
	links 
	{
		"Running"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"RUNNING_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug" 
		defines 
		{
			"RUNNING_DEBUG",
			"RUNNING_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release" 
		defines "RUNNING_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist" 
		defines "RUNNING_DIST"
		runtime "Release"
		optimize "On"
