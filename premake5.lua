workspace "Noz"
	architecture "x86_64"
	
	configurations
	{
		"Debug",
		"Release"
	}

project "Noz"
	location "./Noz/src"
	kind "WindowedApp"
	language "C++"
	
	targetdir ("Binaries/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	objdir ("Binaries/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	
	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"