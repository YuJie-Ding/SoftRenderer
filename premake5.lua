workspace "SoftRenderer"
	startproject "Sandbox"
	architecture "x64"


	configurations 
	{ 
		"Debug",
		"Release" 
	}

	flags
	{
		"MultiProcessorCompile"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SoftRenderer"
	location "SoftRenderer"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	files { "./SoftRenderer/**.h", "./SoftRenderer/**.cpp" }
	staticruntime "off"
   
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"SoftRenderer/"
	}

	defines
	{
		"BUILD_DLL"
	}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	files { "./Sandbox/**.h", "./Sandbox/**.cpp", "./Sandbox/**.ico", "./Sandbox/**.rc" }
	staticruntime "off"
   
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"SoftRenderer/"
	}

	links
	{
		"SoftRenderer"
	}

	defines
	{

	}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
