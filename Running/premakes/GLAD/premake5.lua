project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	location("../../vendor/Glad")

	targetdir ("../../vendor/Glad/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../../vendor/Glad/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"../../vendor/Glad/include/glad/glad.h",
		"../../vendor/Glad/include/KHR/khrplatform.h",
		"../../vendor/Glad/src/glad.c",
	}
	
	includedirs
	{
		"../../vendor/Glad/include"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
