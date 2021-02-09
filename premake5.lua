workspace "RayTracing"
	architecture "x64"
	configurations 
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "RayTraceDemo"
	location "RayTraceDemo"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "rtpch.h"
	pchsource "RayTraceDemo/src/rtpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	filter {"configurations:Debug"}
		defines {"DEBUG"}
		symbols "On"

	filter {"configurations:Release"}
		defines {"NDEBUG"}
		optimize "On"
