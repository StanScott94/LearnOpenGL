workspace "LearnOpenGL"
	architecture "x86_64"
    configurations {
        "Debug",
        "Release"
    }

    startproject "LearnOpenGL"

    flags {
        "MultiProcessorCompile"
    }

    filter "configurations:Debug"
        defines {
            "DEBUG",
            "DEBUG_SHADER"
        }
        symbols "On"

    filter "configurations:Release"
        defines {
            "RELEASE"
        }
        optimize "Speed"
        flags {
            "LinkTimeOptimization"
        }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "LearnOpenGL"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	architecture "x86_64"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "include/",
        "libs/glad/include/",
        "libs/glfw/include/",
        "libs/glm/",
        "libs/imgui/",
        "libs/imgui/examples" 
    }
    
    files {
        "src/**.cpp",
        "src/**.h"
    }

    links {
        "GLFW",
        "GLM",
        "GLAD",
        "ImGui" 
    }

    filter "system:linux"
        links {
            "dl",
            "pthread" 
        }
        defines {
            "_X11"
        }

    filter "system:windows"
        defines {
            "_WINDOWS"
        }

include "libs/glfw.lua"
include "libs/glad.lua"
include "libs/glm.lua"
include "libs/imgui.lua"