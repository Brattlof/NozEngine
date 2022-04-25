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
		"$(VULKAN_SDK)/Include",
		"%{wks.location}/Noz/src",
		"%{wks.location}/Noz/vendor/glfw/include",
		"%{wks.location}/Noz/vendor/glm",
		"%{wks.location}/Noz/vendor/fmt/include",
		"%{wks.location}/Noz/vendor/imgui"
	}
	
include "Noz"
include "Noz_Playground"