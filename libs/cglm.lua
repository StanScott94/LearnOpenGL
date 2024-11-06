OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("CGLM")
kind("StaticLib")
language("C")
platforms({ "x64", "x86" })

targetdir("../bin/" .. OUTPUT_DIR .. "/%{prj.name}")
objdir("../bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

includedirs({ "submodules/cglm/include" })

files({ "submodules/cglm/src/**.c", "submodules/cglm/include/**.h" })

filter("system:linux")
pic("On")

systemversion("latest")
staticruntime("On")

defines({
	"_GLM_X11",
})

filter("system:windows")
systemversion("latest")
staticruntime("On")

defines({
	"_GLM_WIN32",
	"_CRT_SECURE_NO_WARNINGS",
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
