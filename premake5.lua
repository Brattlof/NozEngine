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
		"%{wks.location}/Noz/src"
	}
	
include "Noz"
include "Noz_Playground"