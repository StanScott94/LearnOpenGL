cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

include_directories(include
                    libs/glad/include
                    libs/submodules/glfw/include
                    libs/submodules/glm
                    libs/submodules/imgui
                    libs/submodules/stb)

file(GLOB_RECURSE PROJECT_HEADERS src/*.h)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_SHADERS shaders/*.comp
                                  shaders/*.frag
                                  shaders/*.geom
                                  shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitignore
                         .gitmodules
                         .nvimrc)
file(GLOB IMGUI_SOURCES libs/submodules/imgui/*.cpp
                        libs/submodules/imgui/backends/imgui_impl_glfw.cpp
                        libs/submodules/imgui/backends/imgui_impl_opengl3.cpp)
file(GLOB GLAD_SOURCES libs/glad/src/glad.c)
file(GLOB STB_SOURCES libs/stb/src/stbimage.cpp)

add_definitions(-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_SHADERS}
    ${PROJECT_CONFIGS}
    ${IMGUI_SOURCES}
    ${GLAD_SOURCES}
    ${STB_SOURCES}
)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(libs/submodules/glfw)

target_link_libraries(
    ${PROJECT_NAME}
    glfw
    ${CMAKE_DL_LIBS} # Required for dynamic linking on Unix systems
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)

