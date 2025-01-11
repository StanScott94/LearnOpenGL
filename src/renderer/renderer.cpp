#include "renderer.h"
#include <ostream>
#include <string>
#include "gl_utils.h"
#include "../game/camera/camera.h"
#include "../game/physics/shape.h"
#include "../game/physics/gjk.h"


float fov = 45.0f;
float rotation = 0.0f;
float translationX = 2.0f;
float translationY = 2.0f;
float translationZ = 0.0f;

Shape shape1(1.0f, 1.0f, 1.0f);
Shape shape2(1.0f, 1.0f, 1.0f);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

GJK gjk;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = 0.0f;
float lastY = 0.0f;
bool firstMouse = true;

glm::mat4 identityMatrix = glm::mat4(1.0f);

unsigned int texture1, texture2;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

Renderer::Renderer(Shader &shader, Window &window): shader(shader), window(window) {
    stbi_set_flip_vertically_on_load(true);
}

Renderer::~Renderer() {
}

bool Renderer::Create() {
    
    GLFWwindow *glfwWindow = window.GetGlfwWindow();
    glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);
    glfwSetCursorPosCallback(glfwWindow, mouseCallback);
    glfwSetScrollCallback(glfwWindow, scrollCallback);
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    auto [scrWidth, scrHeight] = window.GetSize();
    lastX = scrWidth / 2.0f;
    lastY = scrHeight / 2.0f;

    GL(glGenVertexArrays(1, &vao));
    GL(glGenBuffers(1, &vbo));

    GL(glBindVertexArray(vao));

    GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL(glBufferData(GL_ARRAY_BUFFER, shape1.GetSizeVertices(), shape1.GetVertices().data(), GL_STATIC_DRAW));

    // position attribute
    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
    GL(glEnableVertexAttribArray(0));

    // color attribute
    GL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
    GL(glEnableVertexAttribArray(1));


    GL(glGenTextures(1, &texture1));
    GL(glBindTexture(GL_TEXTURE_2D, texture1));

    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    int width, height, nrChannels;

    std::string filePath = "resources/container.jpg";
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        GL(glGenerateMipmap(GL_TEXTURE_2D));
    } else {
        std::cout << "Failed to load texture 1" << "\n";
    }
    stbi_image_free(data);

    GL(glGenTextures(1, &texture2));
    GL(glBindTexture(GL_TEXTURE_2D, texture2));

    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    filePath = "resources/awesomeface.png";
    data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        GL(glGenerateMipmap(GL_TEXTURE_2D));
    } else {
        std::cout << "Failed to load texture 2" << "\n";
    }
    stbi_image_free(data);

    shader.Bind();
    shader.Uniform1f("texture1", 0);
    shader.Uniform1f("texture2", 1);

    return true;
}

void Renderer::Destroy() {
    GL(glDeleteBuffers(1, &vbo));
    GL(glDeleteVertexArrays(1, &vao));
}

void Renderer::Draw() {
    ProcessInput(window.GetGlfwWindow());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    shader.Bind();
    auto [scrWidth, scrHeight] = window.GetSize();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
    shader.UniformMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    shader.UniformMat4("view", view);

    glBindVertexArray(vao);
    glm::mat4 model = identityMatrix;
    model = glm::translate(model, glm::vec3(2.0f, 2.0f, 0.0f));
    shape1.UpdateVertices(model);
    shader.UniformMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = identityMatrix;
    model = glm::translate(model, glm::vec3(translationX, translationY, translationZ));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    shape2.UpdateVertices(model);
    shader.UniformMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    shader.Unbind();

    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    bool a = gjk.colistion(shape1, shape2);
    std::cout << "\ncolision: " << a << std::endl;
}

void Renderer::ProcessInput(GLFWwindow *window) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        //camera.ProcessKeyboard(FORWARD, deltaTime);
        translationY += 0.05f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        //camera.ProcessKeyboard(BACKWARD, deltaTime);
        translationY -= 0.05f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        //camera.ProcessKeyboard(LEFT, deltaTime);
        translationX -= 0.05f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        //camera.ProcessKeyboard(RIGHT, deltaTime);
        translationX += 0.05f;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        //camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        //camera.ProcessKeyboard(DOWN, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        translationZ -= 0.05f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        translationZ += 0.05f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        rotation += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        rotation -= 1.0f;
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void Renderer::DrawImGui() {
#ifdef DEBUG
    ImGui::Begin("Renderer");
    ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
    ImGui::End();
#endif
}

