workspace("LearnOpenGL")
platforms({ "x64", "x86" })
configurations({ "Debug", "Release" })
startproject("LearnOpenGL")

flags({ "MultiProcessorCompile" })

filter("configurations:Debug")
defines({ "DEBUG", "DEBUG_SHADER" })
symbols("On")

filter("configurations:Release")
defines({ "RELEASE" })
optimize("Speed")
flags({ "LinkTimeOptimization" })

OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("LearnOpenGL")
kind("ConsoleApp")
language("C")
buildoptions({ "-std=c11" })

targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

includedirs({
	"include/",
	"libs/glad/include/",
	"libs/submodules/glfw/include/",
	"libs/submodules/cglm/include/",
	"libs/submodules/stb/",
})

files({
	"src/**.c",
	"src/**.h",
})

links({
	"GLFW",
	"GLAD",
	"CGLM",
	"STB",
}) -- Use UNIX-style commands for compatibility with Cygwin and macOS

postbuildcommands({
	'if [ ! -d "%{cfg.targetdir}/shaders" ]; then mkdir -p "%{cfg.targetdir}/shaders"; fi',
	'cp shaders/*.vert "%{cfg.targetdir}/shaders/"',
	'cp shaders/*.frag "%{cfg.targetdir}/shaders/"',
})

filter("system:macosx")
toolset("clang")
links({
	"Cocoa.framework",
	"IOKit.framework",
	"CoreFoundation.framework",
	"QuartzCore.framework",
	"Metal.framework",
})

filter("system:windows")
systemversion("latest")
defines({ "_WINDOWS" })
toolset("gcc")

filter("system:linux")
systemversion("latest")
defines({ "_X11" })
toolset("clang")
links({
	"dl",
	"pthread",
})

filter("platforms:x86")
architecture("x86")

filter("platforms:x64")
architecture("x86_64")

include("libs/glfw.lua")
include("libs/glad.lua")
include("libs/cglm.lua")
include("libs/stb.lua")
