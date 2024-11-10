outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("GLAD")
kind("StaticLib")
language("C")
platforms({ "x64" })

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

includedirs({ "glad/include/" })

files({ "glad/src/glad.c" })

filter("system:linux")
pic("On")

systemversion("latest")
staticruntime("On")

defines({
	"_GLAD_X11",
})

filter("system:windows")
systemversion("latest")
staticruntime("On")

defines({
	"_GLAD_WIN32",
	"_CRT_SECURE_NO_WARNINGS",
})

filter("platforms:x64")
architecture("x86_64")

filter("configurations:Debug")
runtime("Debug")
symbols("on")

filter("configurations:Release")
runtime("Release")
optimize("on")
