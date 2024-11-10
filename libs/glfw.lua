outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("GLFW")
kind("StaticLib")
language("C")
platforms({ "x64" })

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

includedirs({
	"submodules/glfw/include/",
	"submodules/glfw/deps/",
})

files({
	"submodules/glfw/include/GLFW/glfw3.h",
	"submodules/glfw/include/GLFW/glfw3native.h",
	"submodules/glfw/src/internal.h",
	"submodules/glfw/src/platform.h",
	"submodules/glfw/src/mappings.h",
	"submodules/glfw/src/context.c",
	"submodules/glfw/src/init.c",
	"submodules/glfw/src/input.c",
	"submodules/glfw/src/monitor.c",
	"submodules/glfw/src/platform.c",
	"submodules/glfw/src/vulkan.c",
	"submodules/glfw/src/window.c",
	"submodules/glfw/src/egl_context.c",
	"submodules/glfw/src/osmesa_context.c",
	"submodules/glfw/src/null_platform.h",
	"submodules/glfw/src/null_joystick.h",
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
	"submodules/glfw/src/posix_time.h",
	"submodules/glfw/src/posix_thread.h",
	"submodules/glfw/src/posix_module.c",
	"submodules/glfw/src/posix_time.c",
	"submodules/glfw/src/posix_thread.c",
	"submodules/glfw/src/x11_platform.h",
	"submodules/glfw/src/xkb_unicode.h",
	"submodules/glfw/src/x11_init.c",
	"submodules/glfw/src/x11_monitor.c",
	"submodules/glfw/src/x11_window.c",
	"submodules/glfw/src/xkb_unicode.c",
	"submodules/glfw/src/glx_context.c",
	"submodules/glfw/src/linux_joystick.h",
	"submodules/glfw/src/linux_joystick.c",
	"submodules/glfw/src/posix_poll.h",
	"submodules/glfw/src/posix_poll.c",
})

links({
	"X11",
	"Xrandr",
	"Xinerama",
	"Xkb",
	"Xcursor",
	"Xi",
	"Xext",
})

defines({
	"_GLFW_X11",
})

filter("system:macosx")
staticruntime("On")

files({
	"submodules/glfw/src/cocoa_time.h",
	"submodules/glfw/src/cocoa_time.c",
	"submodules/glfw/src/posix_thread.h",
	"submodules/glfw/src/posix_module.c",
	"submodules/glfw/src/posix_thread.c",
	"submodules/glfw/src/cocoa_platform.h",
	"submodules/glfw/src/cocoa_joystick.h",
	"submodules/glfw/src/cocoa_init.m",
	"submodules/glfw/src/cocoa_joystick.m",
	"submodules/glfw/src/cocoa_monitor.m",
	"submodules/glfw/src/cocoa_window.m",
	"submodules/glfw/src/nsgl_context.m",
})

links({
	"Cocoa.framework",
	"IOKit.framework",
	"QuartzCore.framework",
	"CoreFoundation.framework",
})

defines({
	"_GLFW_COCOA",
})

filter("system:windows")
systemversion("latest")
staticruntime("On")
defines({
	"_WIN32",
	"_GLFW_WIN32",
	"_CRT_SECURE_NO_WARNINGS",
})

files({
	"submodules/glfw/src/win32_time.h",
	"submodules/glfw/src/win32_thread.h",
	"submodules/glfw/src/win32_module.c",
	"submodules/glfw/src/win32_time.c",
	"submodules/glfw/src/win32_thread.c",
	"submodules/glfw/src/win32_platform.h",
	"submodules/glfw/src/win32_joystick.h",
	"submodules/glfw/src/win32_init.c",
	"submodules/glfw/src/win32_joystick.c",
	"submodules/glfw/src/win32_monitor.c",
	"submodules/glfw/src/win32_window.c",
	"submodules/glfw/src/wgl_context.c",
})

links({ "gdi32" })

filter("platforms:x64")
architecture("x86_64")

filter("configurations:Debug")
runtime("Debug")
symbols("on")

filter("configurations:Release")
runtime("Release")
optimize("on")
