newoption {
   trigger = "dev",
   description = "Adds to the solutions a couple of directories used for developpement"
}

workspace "MacroPad"
	architecture "x64"
	startproject "MacroPad"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "latest"

		defines "MP_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines 
		{
			"MP_DEBUG",
			"PROFILING"
		}
		symbols "On"

	filter "configurations:Release"
		defines "MP_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MP_DIST"
		optimize "On"
		flags "NoIncrementalLink"

	filter {}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--	IncludeDir = {}
--	IncludeDir["GLFW"] = "MacroPadCommons/vendor/GLFW/include"

--	group "Dependecies"
--		include "MacroPadCommons/vendor/GLFW"
--	group ""

project "MacroPad"
	location "MacroPad"
	kind "ConsoleApp"
	language "C++"
	callingconvention ("StdCall")

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"MacroPadCommons/vendor/spdlog/include",
		"MacroPadCommons/src"
	}

	links "MacroPadCommons"

project "MacroPadCommons"
	location "MacroPadCommons"
	kind "SharedLib"
	language "C++"
	callingconvention ("StdCall")

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	pchheader "mppch.h"
	pchsource "%{prj.name}/src/mppch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		--"%{IncludeDir.GLFW}"
	}

	links
	{
		--"GLFW",
		--"opengl32.lib"
	}

	filter "system:windows"
		defines "MP_BUILD_COMMONS"

		postbuildcommands
		{
			("echo %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/MacroPad"),
			("{COPYDIR} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/MacroPad/\""),
			("{COPYDIR} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Testing/\"")
		}

project "PluginTemplate"
	location "PluginTemplate"
	kind "SharedLib"
	language "C++"
	callingconvention ("StdCall")

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"MacroPadCommons/src",
		"MacroPadCommons/vendor/spdlog/include",
		"%{prj.name}/src"
	}

	links { "MacroPadCommons" }

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "latest"

		defines
		{
			"MP_PLATFORM_WINDOWS",
			"MP_BUILD_PLUGIN"
		}

		postbuildcommands
		{
			("{COPYDIR} %{cfg.buildtarget.relpath} ../MacroPad/plugins")
		}

	filter "configurations:Debug"
		defines "MP_PLUGIN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MP_PLUGIN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MP_PLUGIN_DIST"
		optimize "On"
		flags "NoIncrementalLink"

project "PluginTest"
	location "PluginTest"
	kind "SharedLib"
	language "C++"
	callingconvention ("StdCall")

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"MacroPadCommons/src",
		"MacroPadCommons/vendor/spdlog/include",
		"%{prj.name}/src"
	}

	links "MacroPadCommons"

	filter "system:windows"

		defines "MP_BUILD_PLUGIN"

		postbuildcommands
		{
			("{COPYDIR} %{cfg.buildtarget.relpath} ../MacroPad/plugins")
		}

	filter "configurations:Debug"
		defines "MP_PLUGIN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MP_PLUGIN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MP_PLUGIN_DIST"
		optimize "On"

if _OPTIONS["dev"] then
	group "Dev"
		project "DevSandbox"
			location "dev/sandbox"
			kind "SharedLib"
			language "C++"

			targetdir ("bin/" .. outputdir .. "/%{prj.name}")
			objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

			files {
				"%{prj.location}/src/**.h",
				"%{prj.location}/src/**.cpp",
			}

			includedirs
			{
				"MacroPadCommons/src",
				"MacroPadCommons/vendor/spdlog/include",
				"D:/libs/wxWidget/3.1.3/include",
				"%{prj.location}/src"
			}

			links{
				"MacroPadCommons"
			}

			vpaths {
			   ["headers"] = "**.h",
			   ["src/*"] = {"**.c", "**.cpp"}
			}

			filter "system:windows"
				defines "MP_BUILD_PLUGIN"

			filter "configurations:Debug"
				defines "MP_PLUGIN_DEBUG"
				symbols "On"

			filter "configurations:Release"
				defines "MP_PLUGIN_RELEASE"
				optimize "On"

			filter "configurations:Dist"
				defines "MP_PLUGIN_DIST"
				optimize "On"

		project "DevTools"
			location "dev/tools"
			kind "None"
			files {
				"premake5.lua",
				"generate_project.ps1"
			}
			vpaths {
				["Build"] = { "premake5.lua", "generate_project.ps1" }
			}

		project "Testing"
			location "Testing"
			kind "ConsoleApp"
			language "C++"
			callingconvention ("StdCall")

			targetdir ("bin/" .. outputdir .. "/%{prj.name}")
			objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

			files
			{
				"%{prj.name}/tests/**.h",
				"%{prj.name}/tests/**.cpp"
			}

			includedirs
			{
				"vendor/GTest/googletest/include",
				"%{prj.name}/tests",
				"MacroPadCommons/vendor/spdlog/include",
				"MacroPadCommons/src"
			}

			links { "MacroPadCommons", "GTest" }
	group ""
end

group "Dependecies"
	project "GTest"
		location "vendor/GTest/googletest"
			kind "StaticLib"
			language "C++"
			callingconvention ("StdCall")

			targetdir ("bin/" .. outputdir .. "/%{prj.name}")
			objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

			googletestdir = "vendor/%{prj.name}/googletest/"
			sourcedir = googletestdir .. "src/"

			files
			{
				sourcedir .. "**.cc",
				sourcedir .. "**.h"
			}

			includedirs
			{
				googletestdir,
				googletestdir .. "include"
			}
group ""