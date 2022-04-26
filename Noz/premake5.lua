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
		"./src/**.hpp",
		"./src/**.h",
		"./src/**.cpp"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	libdirs
	{
		"$(VULKAN_SDK)/Lib",
		"%{wks.location}/Noz/vendor/libs"
	}
	
	links
	{
		"glfw3",
		"vulkan-1",
		"VkLayer_utils"
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
		