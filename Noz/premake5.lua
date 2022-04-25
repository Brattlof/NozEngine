project "Noz"
	location "./src"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	
	targetdir ("%{wks.location}/Binaries/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	objdir ("%{wks.location}/Binaries/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	
	files
	{
		"./src/**.hpp",
		"./src/**.h",
		"./src/**.cpp"
	}
	
	libdirs
	{
		"$(VULKAN_SDK)/Lib"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "NOZ_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "NOZ_RELEASE"
		runtime "Release"
		optimize "on"
		