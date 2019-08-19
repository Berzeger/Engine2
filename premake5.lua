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
IncludeDir["Glad"] = "Running/vendor/Glad"
IncludeDir["ImGui"] = "Running/vendor/ImGui"

include "Running/premakes/GLFW"
include "Running/premakes/Glad"
include "Running/premakes/ImGui"
	
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
		"%{IncludeDir.GLFW}/include",
		"%{IncludeDir.Glad}/include",
		"%{IncludeDir.ImGui}"
	}
	
	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"RUNNING_PLATFORM_WINDOWS",
			"RUNNING_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
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
