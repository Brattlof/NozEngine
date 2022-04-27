project "Noz_Playground"
	location "./src"
	language "C++"
	cppdialect "C++20"
	
	targetdir ("%{wks.location}/Binaries/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	objdir ("%{wks.location}/Binaries/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
	
	files
	{
		"./src/**.hpp",
		"./src/**.cpp"
	}

	links
	{
		"Noz"
	}
		
	filter "configurations:Debug"
		kind "ConsoleApp"
		defines "NOZ_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		kind "WindowedApp"
		defines "NOZ_RELEASE"
		runtime "Release"
		optimize "on"