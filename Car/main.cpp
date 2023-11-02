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

/*bool loadShaders(GLuint& program) {
    bool loadSuccess = true;
    char infoLog[512];
    GLint success;

    std::string temp = "";
    std::string src = "";

    std::ifstream in_file;

    // Vertex
    in_file.open("vertex_core.glsl");

    if (in_file.is_open()) {
        while (std::getline(in_file, temp)) {
            src += temp + "\n";
        }
    }
    else {
        std::cout << "[!] COULD NOT OPEN VERTEX FILE" << "\n";
        loadSuccess = false;
    }

    in_file.close();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertSrc = src.c_str();
    glShaderSource(vertexShader, 1, &vertSrc, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "[!] COULD NOT COMPILE VERTEX SHADER" << "\n";
        std::cout << infoLog << "\n";
        loadSuccess = false;
    }

    temp = "";
    src = "";

    // Fragment
    in_file.open("fragment_core.glsl");

    if (in_file.is_open()) {
        while (std::getline(in_file, temp)) {
            src += temp + "\n";
        }
    }
    else {
        std::cout << "[!] COULD NOT OPEN FRAGMENT FILE" << "\n";
        loadSuccess = false;
    }

    in_file.close();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragSrc = src.c_str();
    glShaderSource(fragmentShader, 1, &fragSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "[!] COULD NOT COMPILE FRAGMENT SHADER" << "\n";
        std::cout << infoLog << "\n";
        loadSuccess = false;
    }

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "[!] COULD NOT LINK PROGRAM" << "\n";
        std::cout << infoLog << "\n";
        loadSuccess = false;
    }

    glUseProgram(0);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return loadSuccess;
}*/

void updateInput(GLFWwindow* window, Mesh &mesh) {
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
        640, 480,
        4, 4,
        false);

    while (!game.getWindowShouldClose()) {
        // UPDATE INPUT
        game.update();
        game.render();
        
    }
    return 0;
}