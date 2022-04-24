workspace "Noz"
	architecture "x86_64"
	startproject "Noz_Playground"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
	includedirs
	{
		"%{wks.location}/Noz/src",
		"%{wks.location}/Noz/vendor/glfw/include",
		"%{wks.location}/Noz/vendor/glm",
		"%{wks.location}/Noz/vendor/fmt/include"
	}
	
include "Noz"
include "Noz_Playground"