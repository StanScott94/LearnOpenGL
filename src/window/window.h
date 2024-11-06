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

Window* Window_Create(const char *title, unsigned int width, unsigned int height, int vsync);

void Window_Destroy(Window *window);

int Window_Init(Window *window);

void Window_Update(Window *window);

int Window_ShouldClose(Window *window);

int Window_IsVsync(Window *window);

void Window_SetVsync(Window *window, int vsync);

void Window_GetSize(Window *window, int size[2]);
