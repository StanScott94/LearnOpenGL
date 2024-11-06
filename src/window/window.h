#pragma once

#include "engine.h"

typedef struct {
    const char *title;
    unsigned int width, height;
    int vsync;
} WindowData;

typedef struct {
    GLFWwindow *m_Window;
    WindowData m_Data;
} Window;

// Function declarations
Window* Window_Create(const char *title, unsigned int width, unsigned int height, int vsync);
void Window_Destroy(Window *window);

void Window_Update(Window *window);
int Window_ShouldClose(Window *window);

int Window_IsVsync(Window *window);
void Window_SetVsync(Window *window, int vsync);

GLFWwindow *Window_GetGlfwWindow(Window *window);
WindowData *Window_GetDataPointer(Window *window);

glm::ivec2 Window_GetSize(Window *window);

