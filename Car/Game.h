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

	double velocity[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	double maxVelocity = 0.2f;
	
	float velocidadRotacionMaxima = 1.f;
	float velocidadRotacion[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	float friction_coefficient = 0.15;

	/*using clock = std::chrono::steady_clock;
	std::chrono::time_point<clock> start, end;*/

	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//Mode
	int startGame = 0;

	//PlayMode
	bool flag = false;
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

	//Checkpoints
	int checkpointsPassed = 0;
	int aux = 0;
	int lap = 1;

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

	//Checkpoints
	std::vector<Checkpoint*> checkpoints;

	// HAY QUE INICIALIZARLOS DE ALGUNA FORMA Y PONER EL PRIMERO EN DEFAULT SIEMPRE
	//Replays
	int selectedReplayIndex = -1;
	std::vector<std::string> replayNames = { "Hola" , "David", "Aqui", "Los", "Replays", "Xd",
											"aedds", "sdaa", "sda", "dsada", "asdasd", "adsada",
											"sdad", "asdadas", "asdadas"};
	
	
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
	void initCheckpoints();
	
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

	// Partida Time
	std::chrono::steady_clock::time_point startTime;
	bool startTimeStatus = false;
	std::chrono::steady_clock::time_point startTime2;
	bool startTime2Status = false;
	bool flag1 = false,	flag2 = false;

	// Files
	std::string saveFile = "default.txt";

	//States
	std::vector<std::vector<GameState>> carStates;
	std::vector<GameState> gameStates;
	
	//Delta time
	float dt;
	float curTime;
	float lastTime;

	virtual ~Game();

	//Accessors
	int getWindowShouldClose();
	GLFWwindow* getWindow() { return window; }
	int getStartGame() { return startGame; }

	//Modifiers
	void setWindowShouldClose();

	//ImGui
	int menuPrincipal();
	void menuInformation();
	void replaySelector();

	//Functions
	void updateDt();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	
	//PlayMode
	void velocityUI();
	void timeUI();
	void mapUI();
	void updatePlay(int model_number);
	void renderPlay();
	void lapUI();
	void countDownUI(bool &flag);
	void reset();
	void startRaceTimer();
	void startCountdownTimer();
	void saveGameStates();
	

	//ViewMode
	void menuCams();
	void loadGameStates(std::string filename);
	void updateViewCams();
	void updateView(int carStates_number, int car_number);
	void renderView();
	void clearFile(const std::string& filename);
	void camerasPlayers(int player, int typeCam);
	void camerasCircuit(int typeCam);
	void specialCams(int typeCam);
	void cameraAutomatic();

	//Static functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
};