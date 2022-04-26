workspace "Noz"
	architecture "x86_64"
	startproject "Noz_Playground"
	staticruntime "on"
	warnings "Off" -- Don't have time to fix warnings and can't stand to look at them
	
	configurations
	{
		"Debug",
		"Release"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"BX_CONFIG_DEBUG=0"
	}
	
	includedirs
	{
		"$(VULKAN_SDK)/Include",
		"%{wks.location}/Noz/src",
		"%{wks.location}/Noz/vendor/glfw/include",
		"%{wks.location}/Noz/vendor/glm",
		"%{wks.location}/Noz/vendor/fmt/include",
		"%{wks.location}/Noz/vendor/imgui",
		"%{wks.location}/Noz/vendor/bx/include",
		"%{wks.location}/Noz/vendor/bimg/include",
		"%{wks.location}/Noz/vendor/bgfx/include"
	}
	
include "Noz"
include "Noz_Playground"