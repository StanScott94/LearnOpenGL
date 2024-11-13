workspace("LearnOpenGL")
platforms({ "x64" })
configurations({
	"Debug",
	"Release",
})

startproject("LearnOpenGL")
flags({ "MultiProcessorCompile" })

filter("configurations:Debug")
staticruntime("Off")
runtime("Debug")
defines({ "DEBUG", "DEBUG_SHADER" })
symbols("On")

filter("configurations:Release")
staticruntime("Off")
runtime("Release")
defines({ "RELEASE" })
optimize("Speed")
flags({ "LinkTimeOptimization" })

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("LearnOpenGL")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")
toolset("clang")
buildoptions({ "-MJbuild/json_fragments/%{file.basename}.json" })
windowstargetdir = "bin\\" .. outputdir .. "\\%{prj.name}"
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
links({ "OpenGL32", "gdi32" })

postbuildcommands({
	"mkdir " .. windowstargetdir .. "\\shaders",
	"copy shaders\\*.vert " .. windowstargetdir .. "\\shaders",
	"copy shaders\\*.frag " .. windowstargetdir .. "\\shaders",
})

filter("platforms:x64")
architecture("x86_64")

include("libs/glfw.lua")
include("libs/glad.lua")
include("libs/glm.lua")
include("libs/imgui.lua")
include("libs/stb.lua")

newaction({
	trigger = "generate_compile_commands",
	description = "Generate compile_commands.json",
	execute = function()
		local jsonFile = io.open("compile_commands.json", "w")
		jsonFile:write("[\n")

		local include_dirs = {
			"src/**.cpp",
			"src/**.hpp",
			"include/**.h",
			"libs/submodules/**.cpp",
			"libs/submodules/**.hpp",
			"libs/submodules/**.c",
			"libs/submodules/**.h",
		}

		local compiler_flags = "-Iinclude -std=c++17"

		local first = true
		for _, pattern in ipairs(include_dirs) do
			for _, file in ipairs(os.matchfiles(pattern)) do
				-- Separate entries with a comma, as required in JSON syntax
				if not first then
					jsonFile:write(",\n")
				else
					first = false
				end

				local command = string.format(
					'  { "directory": "%s", "command": "g++ %s -c %s", "file": "%s" }',
					os.getcwd(),
					compiler_flags,
					file,
					file
				)
				jsonFile:write(command)
			end
		end

		jsonFile:write("\n]\n")
		jsonFile:close()
	end,
})
