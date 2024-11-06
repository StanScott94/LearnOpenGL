outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("GLFW")
kind("StaticLib")
language("C")
platforms({ "x64", "x86" })

targetdir("../bin/" .. OUTPUT_DIR .. "/%{prj.name}")
objdir("../bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

includedirs({ "submodules/glfw/include/" })

files({
	--		"submodules/glfw/include/GLFW/glfw3.h",
	--		"submodules/glfw/include/GLFW/glfw3native.h",
	"submodules/glfw/src/glfw_config.h",
	"submodules/glfw/src/context.c",
	"submodules/glfw/src/init.c",
	"submodules/glfw/src/input.c",
	"submodules/glfw/src/monitor.c",
	"submodules/glfw/src/vulkan.c",
	"submodules/glfw/src/window.c",
	"submodules/glfw/src/platform.c",
	"submodules/glfw/src/null_init.c",
	"submodules/glfw/src/null_monitor.c",
	"submodules/glfw/src/null_window.c",
	"submodules/glfw/src/null_joystick.c",
})

filter("system:linux")
pic("On")

systemversion("latest")
staticruntime("On")

files({
	"submodules/glfw/src/x11_init.c",
	"submodules/glfw/src/x11_monitor.c",
	"submodules/glfw/src/x11_window.c",
	"submodules/glfw/src/xkb_unicode.c",
	"submodules/glfw/src/posix_time.c",
	"submodules/glfw/src/posix_thread.c",
	"submodules/glfw/src/glx_context.c",
	"submodules/glfw/src/egl_context.c",
	"submodules/glfw/src/osmesa_context.c",
	"submodules/glfw/src/linux_joystick.c",
	"submodules/glfw/src/posix_module.c",
	"submodules/glfw/src/posix_poll.c",
})

defines({
	"_GLFW_X11",
})

filter("system:macosx")
staticruntime("On")

files({
	"submodules/glfw/src/cocoa_init.m",
	"submodules/glfw/src/cocoa_joystick.m",
	"submodules/glfw/src/cocoa_monitor.m",
	"submodules/glfw/src/cocoa_window.m",
	"submodules/glfw/src/cocoa_time.c",
	"submodules/glfw/src/posix_thread.c",
	"submodules/glfw/src/nsgl_context.m",
	"submodules/glfw/src/egl_context.c",
	"submodules/glfw/src/osmesa_context.c",
	"submodules/glfw/src/posix_module.c",
})

defines({
	"_GLFW_COCOA",
})

filter("system:windows")
systemversion("latest")
staticruntime("On")

files({
	"submodules/glfw/src/win32_init.c",
	"submodules/glfw/src/win32_joystick.c",
	"submodules/glfw/src/win32_monitor.c",
	"submodules/glfw/src/win32_time.c",
	"submodules/glfw/src/win32_thread.c",
	"submodules/glfw/src/win32_window.c",
	"submodules/glfw/src/wgl_context.c",
	"submodules/glfw/src/egl_context.c",
	"submodules/glfw/src/osmesa_context.c",
	"submodules/glfw/src/win32_module.c",
})

defines({
	"_GLFW_WIN32",
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

