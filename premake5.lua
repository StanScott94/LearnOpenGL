workspace("LearnOpenGL")
platforms({ "x64" })
configurations({
	"Debug",
	"Release",
})

startproject("LearnOpenGL")
flags({ "MultiProcessorCompile" })

filter("toolset:clang")
toolset("gcc")

filter("configurations:Debug")
staticruntime("On")
runtime("Debug")
defines({ "DEBUG", "DEBUG_SHADER" })
symbols("On")

filter("configurations:Release")
staticruntime("On")
runtime("Release")
defines({ "RELEASE" })
optimize("Speed")
flags({ "LinkTimeOptimization" })

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("LearnOpenGL")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

includedirs({
	"include",
	"libs/glad/include",
	"libs/submodules/glfw/include",
	"libs/submodules/glm",
	"libs/submodules/imgui",
	"libs/submodules/imgui/examples",
	"libs/submodules/stb",
})

files({
	"src/**.cpp",
	"src/**.h",
})

links({
	"gdi32",
	"GLFW",
	"GLAD",
	"ImGui",
	"STB",
})

filter("system:linux")
systemversion("latest")
links({
	"dl",
	"pthread",
})
defines({ "_X11" })

postbuildcommands({
	"{MKDIR} %{cfg.targetdir}/shaders",
	"{COPY} shaders/*.vert %{cfg.targetdir}/shaders",
	"{COPY} shaders/*.frag %{cfg.targetdir}/shaders",
})

filter("system:macosx")
links({
	"Cocoa.framework",
	"IOKit.framework",
	"CoreFoundation.framework",
	"QuartzCore.framework",
	"Metal.framework",
})

postbuildcommands({
	"{MKDIR} %{cfg.targetdir}/shaders",
	"{COPY} shaders/*.vert %{cfg.targetdir}/shaders",
	"{COPY} shaders/*.frag %{cfg.targetdir}/shaders",
})

filter("system:windows")
systemversion("latest")
defines({ "_WINDOWS" })
links({ "OpenGL32" })

postbuildcommands({
	"{MKDIR} %{cfg.targetdir}\\shaders",
	"{COPY} shaders\\*.vert %{cfg.targetdir}\\shaders",
	"{COPY} shaders\\*.frag %{cfg.targetdir}\\shaders",
})

filter("platforms:x64")
architecture("x86_64")

include("libs/glfw.lua")
include("libs/glad.lua")
include("libs/glm.lua")
include("libs/imgui.lua")
include("libs/stb.lua")
