#pragma once

#include "libs.h"

//ZOOOOOOOOOOOM IN BEFORE RECORDING!

//ENUMERATIONS
enum shader_enum { SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEX_PUSHEEN = 0, TEX_PUSHEEN_SPECULAR, TEX_CONTAINER, TEX_CONTAINER_SPECULAR };
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_QUAD = 0 };

class Game
{
private:
	//Private Variables
	//Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Car Movement
	double engineForce = 10.0f;
	double floor = -5.0f;

	double velocity = 0.0f;
	double maxVelocity = 20.0f;
	
	float velocidadRotacionMaxima = 50.f;
	float velocidadRotacion = 0.0f;

	//Delta time
	float dt;
	float curTime;
	float lastTime;

	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//PlayMode
	int playCam;

	//ImGui Fonts
	ImFont* font1; 
	ImFont* font2; 
	ImFont* font3;
	ImFont* font4;

	//Camera
	Camera camera;

	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	//Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	//Models
	std::vector<Model*> models;

	//Meshes
	std::vector<Mesh*> meshes;

	//Lights
	std::vector<PointLight*> pointLights;

	//Private functions
	//Inits
	void initGLFW();
	void initWindow(const char* title, bool resizable);
	void initGLEW(); //AFTER CONTEXT CREATION!!!
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initOBJModels();
	void initModels();
	void initPointLights();
	void initLights();
	void initUniforms();
	void initImGui();
	
	void drawLoadingScreen(const char* loadingMessage);
	void updateUniforms();

public:
	//Constructors / Destructors
	Game(
		const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable
	);

	virtual ~Game();

	//Accessors
	int getWindowShouldClose();
	GLFWwindow* getWindow() { return window; }

	//Modifiers
	void setWindowShouldClose();

	//ImGui
	int menuPrincipal();
	
	//Functions
	void updateDt();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	
	//PlayMode
	void velocityUI();
	void timeUI();
	void updatePlay();
	void renderPlay();
	void mapUI();

	//ViewMode
	void menuCams();
	void updateView();
	void renderView();

	//Static functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
};