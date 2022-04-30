project "Noz"
	location "./src"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	
	targetdir ("%{wks.location}/Binaries/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	objdir ("%{wks.location}/Binaries/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	
	pchheader "pch.hpp"
	pchsource "src/pch.cpp"
	
	files
	{
		"./src/**.h",
		"./src/**.hpp",
		"./src/**.c",
		"./src/**.cpp"
	}
	
	libdirs
	{
		"%{wks.location}/Noz/precompiled_libs"
	}
	
	links
	{
		"glfw3_mt"
	}
	
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "NOZ_DEBUG"
		runtime "Debug"
		symbols "on"
		links
		{
			"bxDebug",
			"bimgDebug",
			"bgfxDebug"
		}
		
	filter "configurations:Release"
		defines "NOZ_RELEASE"
		runtime "Release"
		optimize "on"
		links
		{
			"bxRelease",
			"bimgRelease",
			"bgfxRelease"
		}
		