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
	
project "Running"
	location "Running"
	kind "SharedLib"
	language "C++"
	
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
		"%{prj.name}/vendor/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"RUNNING_PLATFORM_WINDOWS",
			"RUNNING_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug" 
		defines "RUNNING_DEBUG"
		symbols "On"
		
	filter "configurations:Release" 
		defines "RUNNING_RELEASE"
		optimize "On"
		
	filter "configurations:Dist" 
		defines "RUNNING_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
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
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"RUNNING_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug" 
		defines "RUNNING_DEBUG"
		symbols "On"
		
	filter "configurations:Release" 
		defines "RUNNING_RELEASE"
		optimize "On"
		
	filter "configurations:Dist" 
		defines "RUNNING_DIST"
		optimize "On"