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

double lastTime = glfwGetTime();
int nbFrames = 0;


void fpsCounter(GLFWwindow* window) {
    double currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
        // printf and reset timer
        // Set the window title
        double fps = static_cast<double>(nbFrames) / (currentTime - lastTime);
        std::string title = std::to_string(fps);
        glfwSetWindowTitle(window, title.c_str());
        nbFrames = 0;
        lastTime = currentTime;
    }
}

std::string getCurrentDateTime() {
    const int bufferSize = 80; // Size of the buffer to hold the date and time
    char buffer[bufferSize]; // Buffer to store the formatted date and time

    // Get current time
    std::time_t currentTime = std::time(nullptr);

    struct tm timeInfo;
    localtime_s(&timeInfo, &currentTime);

    // Format the time into a string
    std::strftime(buffer, bufferSize, "gamestates_%Y_%m_%d_%H%M%S.txt", &timeInfo);

    return std::string(buffer);
}

const double FIXED_TIMESTEP = 16.7; // in milliseconds

auto currentTime = std::chrono::steady_clock::now();
auto accumulator = 0.0;

int main(void)
{
    Game game("Racing Game",
        1280, 720,
        3, 3,
        true);

    game.loadGameStates("red_npc.txt");
    game.loadGameStates("blue_npc.txt");
    game.loadGameStates("yellow_npc.txt");
    game.loadGameStates("green_npc.txt");
    game.loadGameStates("purple_npc.txt");

    std::cout << game.gameStates.size() << std::endl;

    static double limitFPS = 1.0 / 60.0;

    double lastTime = glfwGetTime(), timer = lastTime;
    double deltaTime = 0, nowTime = 0;
    int frames = 0, updates = 0;

    while (!game.getWindowShouldClose()) {
        fpsCounter(game.getWindow());
        // UPDATE INPUT
        //std::cout << "Estado de juego: " << startGame << std::endl;
        auto currentTime = std::chrono::steady_clock::now();

        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime) / limitFPS;
        lastTime = nowTime;

        if (game.getStartGame() == 2) {
            if (!game.startTimeStatus) {
                game.dt = 0.0f;
                game.curTime = 0.0f;
                game.lastTime = glfwGetTime();
                nowTime = glfwGetTime();
                deltaTime = 0;
                lastTime = nowTime;
                game.startTimeStatus = true;
            }
            while (deltaTime >= 1.0) {
                game.updateView(0, 1);
                game.updateView(1, 3);
                game.updateView(2, 4);
                game.updateView(3, 5);
                game.updateView(4, 6);
                game.updateViewCams();   // - Update function
                updates++;
                deltaTime--;
            }
            game.renderView();
            game.menuCams();
        }

        
        if (game.getStartGame() == 1) {
            if (!game.flag2) {
                game.updatePlay(1);
                game.flag2 = true;
            }
            // Cuenta atras
            if (!game.flag1) {
                if (!game.startTime2Status) {
                    game.startCountdownTimer();
                    game.startTime2Status = true;
                }
                game.renderPlay();
                game.countDownUI(game.flag1);
            }
            // Empieza el juego
            else if (game.flag1) {
                if (!game.startTimeStatus) {
                    game.saveFile = getCurrentDateTime();
					game.startRaceTimer();
                    game.gameStates.clear();
                    game.dt = 0.0f;
                    game.curTime = 0.0f;
                    game.lastTime = glfwGetTime();
                    //game.clearFile("gamestates.txt");
                    nowTime = glfwGetTime();
                    deltaTime = 0;
                    lastTime = nowTime;
                    std::cout << updates << std::endl;
					game.startTimeStatus = true;
				}
                while (deltaTime >= 1.0) {
                    game.updatePlay(1);
                    game.updateView(1, 3);
                    game.updateView(2, 4);
                    game.updateView(3, 5);
                    game.updateView(4, 6);
                    updates++;
                    deltaTime--;
                }
                //game.updatePlay();
                //game.updateView();
                game.renderPlay();
                game.velocityUI();
                game.timeUI();
                game.lapUI();
                game.mapUI();
            }
        }

        if (game.getStartGame() == 0) {
            int startGame = game.menuPrincipal();
        }

        glfwSwapBuffers(game.getWindow());
        glfwPollEvents();
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));

        frames++;

        // - Reset after one second
        if (glfwGetTime() - timer > 1.0) {
            timer++;
            std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
            updates = 0, frames = 0;
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}