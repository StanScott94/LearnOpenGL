#include "window.h"
#include <stdio.h>
#include <stdlib.h>

void error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void WindowResizeCallback(GLFWwindow *win, int width, int height) {
    WindowData *data = (WindowData *)glfwGetWindowUserPointer(win);
    data->width = width;
    data->height = height;
    glViewport(0, 0, width, height);
    printf("Resized %d, %d\n", data->width, data->height);
}

Window* Window_Create(const char *title, unsigned int width, unsigned int height, int vsync) {
    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) return NULL;

    window->m_Data = (WindowData) {
        .title = title,
        .width = width,
        .height = height,
        .vsync = vsync
    };
    return window;
}

void Window_Destroy(Window* window) {
    if (window) {
        if (window->m_Window) {
            glfwDestroyWindow(window->m_Window);
        }
        glfwTerminate();
        free(window);
    }
}

int Window_Init(Window* window) {
    if (!window) return 0;

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 0;
    }

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    #else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    #endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    printf("GLFW version: %s\n", glfwGetVersionString());

    window->m_Window = glfwCreateWindow(window->m_Data.width, window->m_Data.height, window->m_Data.title, NULL, NULL);

    if (!window->m_Window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 0;
    }

    glfwSetWindowUserPointer(window->m_Window, &(window->m_Data));

    glfwSetWindowSizeCallback(window->m_Window, WindowResizeCallback);

    glfwMakeContextCurrent(window->m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return 0;
    }

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    Window_SetVsync(window, window->m_Data.vsync);

    return 1;
}

void Window_Update(Window* window) {
    if (window && window->m_Window) {
        glfwSwapBuffers(window->m_Window);
        glfwPollEvents();
    }
}

int Window_ShouldClose(Window* window) {
    return window ? glfwWindowShouldClose(window->m_Window) : 1;
}

void Window_GetSize(Window *window, int size[2]) {
    size[0] = window->m_Data.width;
    size[1] = window->m_Data.height;
}

int Window_IsVsync(Window* window) {
    return window ? window->m_Data.vsync : 0;
}

void Window_SetVsync(Window* window, int vsync) {
    if (window) {
        window->m_Data.vsync = vsync;
        glfwSwapInterval(vsync ? 1 : 0);
    }
}
