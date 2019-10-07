workspace "RunningEngine"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}	
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
IncludeDir = {}
IncludeDir["GLFW"] = "Running/vendor/GLFW"
IncludeDir["Glad"] = "Running/vendor/Glad"
IncludeDir["ImGui"] = "Running/vendor/ImGui"
IncludeDir["glm"] = "Running/vendor/glm"

include "Running/premakes/GLFW"
include "Running/premakes/Glad"
include "Running/premakes/ImGui"
	
project "Running"
	location "Running"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Running/src/pch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{IncludeDir.glm}/glm/**.hpp",
		"%{IncludeDir.glm}/glm/**.inl"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}/include",
		"%{IncludeDir.Glad}/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	
	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"RUNNING_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug" 
		defines 
		{
			"RUNNING_DEBUG",
			"RUNNING_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release" 
		defines "RUNNING_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist" 
		defines "RUNNING_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
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
		"Running/src",
		"%{IncludeDir.glm}"
	}
	
	links 
	{
		"Running"
	}
	
	filter "system:windows"
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
		symbols "on"
		
	filter "configurations:Release" 
		defines "RUNNING_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist" 
		defines "RUNNING_DIST"
		runtime "Release"
		optimize "on"
