project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	location("../../vendor/ImGui")

	targetdir ("../../vendor/ImGui/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../../vendor/ImGui/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"../../vendor/ImGui/imconfig.h",
		"../../vendor/ImGui/imgui.h",
		"../../vendor/ImGui/imgui.cpp",
		"../../vendor/ImGui/imgui_draw.cpp",
		"../../vendor/ImGui/imgui_internal.h",
		"../../vendor/ImGui/imgui_widgets.cpp",
		"../../vendor/ImGui/imstb_retpack.h",
		"../../vendor/ImGui/imstb_textedit.h",
		"../../vendor/ImGui/imstb_truetype.h",
		"../../vendor/ImGui/imgui_demo.cpp"
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
