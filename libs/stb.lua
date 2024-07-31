outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "STB"
	kind "StaticLib"
	language "C"
	platforms { "x64", "x86" }

    	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")
	
	includedirs { "submodules/stb/" }

	files { 
		"stb/stbimage.cpp"
	}

	filter "platforms:x86"
	architecture "x86"

	filter "platforms:x64"
	architecture "x86_64"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"