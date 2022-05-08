workspace "Noz"
	architecture "x86_64"
	startproject "Noz_Editor"
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
		"%{wks.location}/Noz/src",
		"%{wks.location}/Noz/vendor/glfw/include",
		"%{wks.location}/Noz/vendor/glm",
		"%{wks.location}/Noz/vendor/fmt/include",
		"%{wks.location}/Noz/vendor/imgui",
		"%{wks.location}/Noz/vendor/imgui/backends",
		"%{wks.location}/Noz/vendor/bx/include",
		"%{wks.location}/Noz/vendor/bimg/include",
		"%{wks.location}/Noz/vendor/bgfx/include",
		"%{wks.location}/Noz/vendor/bgfx/3rdparty",
		"%{wks.location}/Noz/vendor/bgfx/examples/common"
	}
	
	filter "system:windows"
		systemversion "latest"
	
include "Noz"
include "Noz_Editor"