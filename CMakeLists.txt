cmake_minimum_required(VERSION 3.10)

project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

# Include directories
include_directories(
    include
    libs/glad/include
    libs/submodules/glfw/include
    libs/submodules/glm
    libs/submodules/imgui
    libs/submodules/stb
)

# Add source files
file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h)

# Executable
add_executable(LearnOpenGL ${SRC_FILES})

# GLAD - Add GLAD as a static library
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# GLFW
add_subdirectory(libs/submodules/glfw)

# ImGui - Manually add files
file(GLOB IMGUI_SOURCES
    libs/submodules/imgui/*.cpp
    libs/submodules/imgui/backends/imgui_impl_glfw.cpp
    libs/submodules/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})

# Include directories for ImGui
target_include_directories(imgui PUBLIC
    libs/submodules/imgui
    libs/submodules/glfw/include
    libs/glad/include
)

target_compile_definitions(imgui PUBLIC "IMGUI_IMPL_OPENGL_LOADER_GLAD")

# GLM (Header-only)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE libs/submodules/glm)

# STB (Header-only)
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE libs/submodules/stb)

# Link libraries
target_link_libraries(LearnOpenGL
    glad
    glfw
    imgui
    glm
    stb
    ${CMAKE_DL_LIBS} # Required for dynamic linking on Unix systems
)

# macOS-specific settings
if(APPLE)
    target_link_libraries(LearnOpenGL
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework QuartzCore"
        "-framework Metal"
    )
endif()

# Copy shaders after build
add_custom_command(TARGET LearnOpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
)

