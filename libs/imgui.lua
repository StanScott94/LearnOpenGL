outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("ImGui")
kind("StaticLib")
language("C")
platforms({ "x64" })

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

includedirs({ "submodules/imgui/", "glad/include", "submodules/glfw/include/" })

files({
	"submodules/imgui/*.cpp",
	"submodules/imgui/backends/imgui_impl_glfw.cpp",
	"submodules/imgui/backends/imgui_impl_opengl3.cpp",
})

defines({
	"IMGUI_IMPL_OPENGL_LOADER_GLAD",
})

filter("system:linux")
pic("On")
systemversion("latest")
staticruntime("On")

defines({
	"_IMGUI_X11",
})

filter("system:macosx")
staticruntime("On")
cppdialect("C++11")

defines({
	"_IMGUI_COCOA",
})

filter("system:windows")
systemversion("latest")
staticruntime("On")

defines({
	"_IMGUI_WIN32",
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

