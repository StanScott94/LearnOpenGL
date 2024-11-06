outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("STB")
kind("StaticLib")
language("C")
platforms({ "x64", "x86" })

targetdir("../bin/" .. OUTPUT_DIR .. "/%{prj.name}")
objdir("../bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

includedirs({ "submodules/stb/" })

files({
	"stb/stbimage.cpp",
})

filter("platforms:x86")
architecture("x86")

filter("platforms:x64")
architecture("x86_64")

filter("configurations:Debug")
runtime("Debug")
symbols("on")

filter("configurations:Release")
runtime("Release")
optimize("on")

