project "Glad"
	kind "StaticLib"
	language "C"

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
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
