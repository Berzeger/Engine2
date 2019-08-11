workspace "Engine2"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
project "Engine2"
	location "Engine2"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"ENGINE_PLATFORM_WINDOWS",
			"ENGINE_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug" 
		defines "ENGINE_DEBUG"
		symbols "On"
		
	filter "configurations:Release" 
		defines "ENGINE_RELEASE"
		optimize "On"
		
	filter "configurations:Dist" 
		defines "ENGINE_DIST"
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
		"Engine2/vendor/spdlog/include",
		"Engine2/src"
	}
	
	links 
	{
		"Engine2"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"ENGINE_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug" 
		defines "ENGINE_DEBUG"
		symbols "On"
		
	filter "configurations:Release" 
		defines "ENGINE_RELEASE"
		optimize "On"
		
	filter "configurations:Dist" 
		defines "ENGINE_DIST"
		optimize "On"