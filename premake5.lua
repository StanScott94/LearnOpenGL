workspace("LearnOpenGL")
platforms({ "x64", "x86" })
configurations({
	"Debug",
	"Release",
})

startproject("LearnOpenGL")

flags({
	"MultiProcessorCompile",
})

filter("configurations:Debug")
defines({
	"DEBUG",
	"DEBUG_SHADER",
})
symbols("On")

filter("configurations:Release")
defines({
	"RELEASE",
})
optimize("Speed")
flags({
	"LinkTimeOptimization",
})

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("LearnOpenGL")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

includedirs({
	"include/",
	"libs/glad/include/",
	"libs/glfw/include/",
	"libs/glm/",
	"libs/imgui/",
	"libs/imgui/examples",
})

files({
	"src/**.cpp",
	"src/**.h",
})

links({
	"GLFW",
	"GLM",
	"GLAD",
	"ImGui",
})

filter("system:linux")
systemversion("latest")
toolset("clang")
links({
	"dl",
	"pthread",
})
defines({
	"_X11",
})

filter("system:macosx")
links({
	"Cocoa.framework",
        "IOKit.framework",
        "CoreFoundation.framework",
})

filter("system:windows")
systemversion("latest")
defines({
	"_WINDOWS",
})

filter("platforms:x86")
architecture("x86")

filter("platforms:x64")
architecture("x86_64")

include("libs/glfw.lua")
include("libs/glad.lua")
include("libs/glm.lua")
include("libs/imgui.lua")
