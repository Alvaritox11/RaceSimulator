#include "libs.h"
#include "Vertex.h"
#include "Game.h"

/*
The tutorial was released a long time ago but in openGL 4 they introduced a function called glBindTextureUnit() which is just a better way of binding a texture to a unit.

In this case to bind the textures you would simply do:

        glBindTextureUnit(0, texture0);
        glBindTextureUnit(1, texture1);

No need to use GL_TEXTURE0 or any define like that, it will just take an integer with the slot number and the texture id.

In any case someone going through the tutorial sees this
*/

Vertex vertices[] = {
    glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),   glm::vec3(0.f, 0.f, 1.f),
    glm::vec3(-0.5f, -0.5f, 0.f),   glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
    glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(1.f, 1.f, 0.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
    glm::vec3(0.5f, 0.5f, 0.f),    glm::vec3(1.f, 1.f, 0.f),   glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)
};

unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
};

unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

void updateInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) {
    glViewport(0, 0, fbW, fbH);
}

void updateInput(GLFWwindow* window, Mesh& mesh) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mesh.move(glm::vec3(0.f, 0.01f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mesh.move(glm::vec3(0.f, -0.01f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        mesh.move(glm::vec3(-0.01f, 0.f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        mesh.move(glm::vec3(0.01f, 0.f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        mesh.move(glm::vec3(0.f, 0.f, 0.01f));
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        mesh.move(glm::vec3(0.f, 0.f, -0.01f));
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        mesh.rotate(glm::vec3(0.f, 1.f, 0.f));
    }
}

GLFWwindow* createWindow(
    const char* title,
    const int width, const int height,
    int& fbWidth, int& fbHeight,
    const int GLmajorVer, const int GLminorVer,
    bool resizable
) {

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLmajorVer);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLminorVer);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glfwSetFramebufferSizeCallback(window, Game::framebuffer_resize_callback);
    //
    //glViewport(0, 0, framebufferWidth, framebufferHeight);

    glfwMakeContextCurrent(window);

    return window;
}

int main(void)
{
    Game game("Racing Game",
        1280, 720,
        3, 3,
        false);

    int startGame = 0;

    while (!game.getWindowShouldClose()) {
        // UPDATE INPUT
        //std::cout << "Estado de juego: " << startGame << std::endl;

        if (startGame == 2) {
            game.updateView();
            game.renderView();
            game.menuCams();
        }

        
        if (startGame == 1) {
            game.updatePlay();
            game.renderPlay();
            game.velocityUI();
            game.timeUI();
            game.mapUI();
        }

        if (startGame == 0) {
            // Solo renderiza el menú principal si no estás en la vista de menú
            startGame = game.menuPrincipal();
        }

        glfwSwapBuffers(game.getWindow());
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}