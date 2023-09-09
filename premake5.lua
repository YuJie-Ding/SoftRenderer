workspace "SoftRenderer"
	-- startproject "Main"
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

-- project "Application"
-- 	location "Application"
-- 	kind "SharedLib"
-- 	language "C++"
-- 	cppdialect "C++17"
-- 	files { "./Application/**.h", "./Application/**.cpp" }
-- 	staticruntime "off"
   
-- 	targetdir ("bin/" .. outputdir .. "/")
-- 	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

-- 	defines
-- 	{
-- 		"BUILD_DLL"
-- 	}

-- 	filter { "configurations:Debug" }
-- 		defines { "DEBUG" }
-- 		symbols "On"

-- 	filter { "configurations:Release" }
-- 		defines { "NDEBUG" }
-- 		optimize "On"
   
-- project "Main"
	-- location "Main"
	-- kind "ConsoleApp"
	-- language "C++"
	-- cppdialect "C++17"
	-- files { "./Main/**.h", "./Main/**.cpp" }
	-- staticruntime "off"

	-- targetdir ("bin/" .. outputdir .. "/")
	-- objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- includedirs
	-- {
	-- 	"Hello/",
	-- 	"Application/"
	-- }

	-- links
	-- {
	-- 	"Hello",
	-- 	"Application"
	-- }

	-- filter { "configurations:Debug" }
	-- 	defines { "DEBUG" }
	-- 	symbols "On"

	-- filter { "configurations:Release" }
	-- 	defines { "NDEBUG" }
	-- 	optimize "On"