#include "engine.h"
#include "./window/window.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    Window *window = Window_Create("Learn OpenGL", SCR_WIDTH, SCR_HEIGHT, 1);
    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        return -1;
    }

    while (!Window_ShouldClose(window)) {
        glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Window_Update(window);
    }

    Window_Destroy(window);

    return 0;
}
