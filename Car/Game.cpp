#include "Game.h"

// ===============================================================
// Private functions =============================================
// ===============================================================

void Game::initGLFW()
{
	//INIT GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initWindow(const char* title, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); MAC OS

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(window, Game::framebuffer_resize_callback);
	//IMPORTANT WHITH PERSPECTIVE MATRIX!!!

	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(this->window); //IMPORTANT!!
}

void Game::initGLEW()
{
	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//// Configuraciones adicionales de GLFW
	//glfwMakeContextCurrent(this->window);

	//// Configuración del modo de entrada del ratón (punto 1)
	//glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_NORMAL);

	//// Establecer callback de posición del ratón (punto 2)
	//glfwSetCursorPosCallback(this->window, ImGui_ImplGlfw_MousePosCallback);
}

void Game::initMatrices()
{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);
}

void Game::initShaders()
{
	char vertexFile[] = "vertex_core.glsl";
	char fragmentFile[] = "fragment_core.glsl";
	char geometryFile[] = ""; // If it's an empty string
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		vertexFile, fragmentFile));
}

void Game::initTextures()
{
	//TEXTURE 0
	this->textures.push_back(new Texture("Images/pusheen.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/pusheen_specular.png", GL_TEXTURE_2D));

	//TEXTURE 1
	this->textures.push_back(new Texture("Images/pista.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/container_specular.png", GL_TEXTURE_2D));

	// TEXTURE 2
	this->textures.push_back(new Texture("models/Model001_Material1.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/circuit_tex.png", GL_TEXTURE_2D));

	this->textures.push_back(new Texture("images/circuit.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/mask3.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/circuit_borders.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/car_icon2.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/blue.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/preview.jpg", GL_TEXTURE_2D));

	// BACKGROUND
	this->textures.push_back(new Texture("images/backMenu.png", GL_TEXTURE_2D));
}

void Game::initMaterials()
{
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
		0, 1));
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
		4, 4));

	this->materials.push_back(new Material(glm::vec3(1.f), glm::vec3(0.f), glm::vec3(0.f),
		0, -1));

}

void Game::initOBJModels()
{

}

void Game::initModels()
{
	std::vector<Mesh*>meshes;
	std::vector<Mesh*>meshes2;

	Pyramid pyramid_0;
	Quad quad_0;
	Quad quad_1;
	
	this->models.push_back(new Model(
		glm::vec3(2.f, floor, 2.f),
		this->materials[0],
		this->textures[5],
		this->textures[5],
		"models/montmelo2v3.obj"
	)
	);


	this->models.push_back(new Model(
		glm::vec3(-85.f, floor + 0.25, -60.f),
		this->materials[0],
		this->textures[4],
		this->textures[4],
		"models/model.obj"
	)
	);

	this->models.push_back(new Model(
		glm::vec3(-60.f, floor + 100, -75.f),
		this->materials[2],
		this->textures[11],
		this->textures[11],
		"models/skybox/cuboklk.obj"
	)
	);

	models[1]->getMeshes()[0]->rotate(90, glm::vec3(0, 1, 0));

	for (auto*& i : meshes)
		delete i;

	for (auto*& i : meshes2)
		delete i;
}

void Game::initPointLights()
{
	this->pointLights.push_back(new PointLight(glm::vec3(0.f, 150.f, 0.f)));
}

void Game::initLights()
{
	this->initPointLights();
}

void Game::initUniforms()
{
	//INIT UNIFORMS
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	for (PointLight* pl : this->pointLights)
	{
		pl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
	}
}

void Game::initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//alomejor hay que guardarlo en variables
	font1 = io.Fonts->AddFontDefault();
	font2 = io.Fonts->AddFontFromFileTTF(".\\fonts\\race.ttf", 60.0f);
	font3 = io.Fonts->AddFontFromFileTTF(".\\fonts\\velocity.ttf", 20.0f);
	font4 = io.Fonts->AddFontFromFileTTF(".\\fonts\\airstrike.ttf", 50.0f);


	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(this->window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Game::initCheckpoints()
{
	std::vector<glm::vec3> points = { 
					glm::vec3(39, -4.75, -60),
					glm::vec3(131, -4.75, -60),
					glm::vec3(175, -4.75, -22),
					glm::vec3(214, -4.75, 25),
					glm::vec3(137, -4.75, 70),
					glm::vec3(74, -4.75, 50),
					glm::vec3(132, -4.75, 23),
					glm::vec3(154, -4.75, -6),
					glm::vec3(80, -4.75, -33),
					glm::vec3(51, -4.75, -10),
					glm::vec3(11, -4.75, 55),
					glm::vec3(-40, -4.75, 50),
					glm::vec3(-155, -4.75, -17),
					glm::vec3(-175, -4.75, 15),
					glm::vec3(-134, -4.75, 45),
					glm::vec3(-182, -4.75, 52),
					glm::vec3(-201, -4.75, 12),
					glm::vec3(-220, -4.75, -34),
					glm::vec3(-180, -4.75, -60),
					glm::vec3(-85, -4.75, -59)
	};

	for (const auto& point : points) {
		Checkpoint* aux = new Checkpoint(point);
		checkpoints.push_back(aux);
	}
}

void Game::updateUniforms()
{
	//Update view matrix (camera)
	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

	for (PointLight* pl : this->pointLights)
	{
		pl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
	}

	//Update framebuffer size and projection matrix
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}

// ===============================================================
// Pantalla Carga ================================================
// ===============================================================

void Game::drawLoadingScreen(const char* loadingMessage) 
{
	if (this->window == nullptr) {
		std::cerr << "Error: La ventana es nullptr en drawLoadingScreen" << std::endl;
		return;
	}

	// Limpia la pantalla
	glClear(GL_COLOR_BUFFER_BIT);

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoBackground;

	ImVec2 window_size = ImVec2(1000.0f, 200.0f);
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImVec2 window_pos = ImVec2(center.x - window_size.x * 0.5f, center.y - window_size.y * 0.5f);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

	ImGui::Begin("Loading", nullptr, flags);

	ImGui::PushFont(font4);
	const char* title = "LOADING...";
	ImVec2 textSize = ImGui::CalcTextSize(title);
	ImGui::SetCursorPosX((window_size.x - textSize.x) * 0.5f);
	ImGui::Text("%s", title);
	ImGui::PopFont();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

// ===============================================================
// Constructors / Destructors  ===================================
// ===============================================================

Game::Game(
	const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable
)
	:
	WINDOW_WIDTH(WINDOW_WIDTH),
	WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR),
	GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{

	// Init variables
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, 1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this->firstMouse = true;

	// Initialize GLFW and the window
	this->initGLFW();
	this->initWindow(title, resizable);
	this->initImGui();

	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	drawLoadingScreen("LOADING...");

	this->initTextures();
	this->initMaterials();
	this->initOBJModels();
	drawLoadingScreen("LOADING...");

	this->initModels();
	this->initLights();
	this->initUniforms();
	drawLoadingScreen("LOADING...");
	
	this->initCheckpoints();
}

Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->shaders[i];

	for (size_t i = 0; i < this->textures.size(); i++)
		delete this->textures[i];

	for (size_t i = 0; i < this->materials.size(); i++)
		delete this->materials[i];

	for (auto*& i : this->models)
		delete i;

	for (size_t i = 0; i < this->pointLights.size(); i++)
		delete this->pointLights[i];
}

// ===============================================================
// Accesor  ======================================================
// ===============================================================

int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

// ===============================================================
// Modifier  =====================================================
// ===============================================================

void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

// ===============================================================
// ImGui =========================================================
// ===============================================================

int Game::menuPrincipal()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse /*|
		ImGuiWindowFlags_NoBackground*/;

	ImVec2 screen_size = ImGui::GetIO().DisplaySize;

	ImVec2 window_size = screen_size;
	ImVec2 window_pos = ImVec2(0, 0);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

	ImGui::Begin("Ventana ImGui", nullptr, flags);

	GLuint background_texture = this->textures[12]->getID();
	ImVec2 uv_min = ImVec2(0.0f, 0.0f);
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);
	ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)background_texture, window_pos, ImVec2(window_pos.x + window_size.x, window_pos.y + window_size.y), uv_min, uv_max);

	ImGui::PushFont(font4);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	const char* title = "RACE SIMULATOR!";
	ImVec2 textSize = ImGui::CalcTextSize(title);
	ImGui::SetCursorPosY((window_size.y - textSize.y) * 0.2f); // Posición vertical ajustada
	ImGui::SetCursorPosX((window_size.x - textSize.x) * 0.5f);
	ImGui::Text("%s", title);
	ImGui::PopStyleColor();
	ImGui::PopFont();

	ImGui::Dummy(ImVec2(0.0f, 30.0f));
	float buttonWidth = 400.0f;
	float buttonHeight = 40.0f;
	float buttonRounding = 12.0f;

	ImGuiStyle& backupStyle = ImGui::GetStyle();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, buttonRounding);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, .8f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	ImGui::SetCursorPosX((window_size.x - buttonWidth) * 0.5f);
	if (ImGui::Button("START RACE", ImVec2(buttonWidth, 50))) {
		startGame = 1;
		camera.setType(THIRD);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	ImGui::Dummy(ImVec2(0.0f, 10.0f));
	ImGui::SetCursorPosX((window_size.x - buttonWidth) * 0.5f);
	if (ImGui::Button("START VIEW", ImVec2(buttonWidth, 50))) {
		startGame = 2;
		camera.setType(PANORAMICA);
	}
	ImGui::Dummy(ImVec2(0.0f, 10.0f));
	ImGui::SetCursorPosX((window_size.x - buttonWidth) * 0.5f);
	if (ImGui::Button("INFORMATION", ImVec2(buttonWidth, 50))) {

	}
	ImGui::Dummy(ImVec2(0.0f, 10.0f));
	ImGui::SetCursorPosX((window_size.x - buttonWidth) * 0.5f);
	if (ImGui::Button("EXIT", ImVec2(buttonWidth, 50))) {
		glfwSetWindowShouldClose(window, true);
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	ImGui::GetStyle() = backupStyle;

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return startGame;

}

void Game::menuCams()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse /*| 
		ImGuiWindowFlags_NoBackground*/;

	ImVec2 screenSize = ImGui::GetIO().DisplaySize;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// VENTANA PARTICIPANTES

	ImVec2 windowSizeLeft = ImVec2(170.0f, 390.0f);
	ImVec2 windowPosLeft = ImVec2(30.0f, 110.f);

	float buttonWidth = 70.0f;  
	float buttonHeight = 50.0f; 
	float buttonRounding = 12.0f;

	ImGui::SetNextWindowPos(windowPosLeft, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSizeLeft, ImGuiCond_Always);
	ImGui::Begin("Participants", nullptr, flags);

	float backup = font4->Scale;
	font4->Scale = 0.3;
	ImGuiStyle& backupStyle = ImGui::GetStyle();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, buttonRounding);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	for (int i = 0; i < 5; ++i) {
		ImGui::PushFont(font4);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255.0f, 255.0f, 255.0f, 1.0f));
		ImGui::Text("PLAYER %d", i + 1);
		ImGui::PopStyleColor();
		ImGui::PopFont();

		if (ImGui::Button("1st", ImVec2(buttonWidth, buttonHeight))) {
			camera.setCamPlayer(1);
			camera.setFlagPlayer(1);
			camera.setPlayer(i);
		}
		ImGui::SameLine();
		if (ImGui::Button("3rd", ImVec2(buttonWidth, buttonHeight))) {
			camera.setCamPlayer(0);
			camera.setFlagPlayer(1);
			camera.setPlayer(i);
		}
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	ImGui::GetStyle() = backupStyle;
	ImGui::End();

	// VENTANA PANO Y AUTO

	ImVec2 windowSizeTopLeft = ImVec2(220.0f, 50.0f);
	ImVec2 windowPosTopLeft = ImVec2(30.f, 40.0f);

	ImGui::SetNextWindowPos(windowPosTopLeft, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSizeTopLeft, ImGuiCond_Always);
	ImGui::Begin("Pano y Auto", nullptr, flags);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, buttonRounding);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	if (ImGui::Button("Panoramica", ImVec2(100.f, 40.f))) {
		camera.setType(2);
		camera.setFlagPlayer(0);
	}
	ImGui::SameLine();
	if (ImGui::Button("Automatica", ImVec2(100.f, 40.f))) {
		std::cout << "Hola" << std::endl;
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	ImGui::End();

	// VENTANA CAMARA ESCOGIDA

	ImVec2 windowSizeTopRight = ImVec2(220.0f, 50.0f); 
	ImVec2 windowPosTopRight = ImVec2(screenSize.x - windowSizeTopLeft.x - 30.f, 40.0f);

	ImGui::SetNextWindowPos(windowPosTopRight, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSizeTopRight, ImGuiCond_Always);
	ImGui::Begin("Camara", nullptr, flags);

	ImGui::PushFont(font4);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255.0f, 255.0f, 255.0f, 1.0f));

	ImGui::Text("You are visualizing:");
	int cam = camera.getType() - 1;
	if (cam >= 2 && cam <= 14) {
		ImGui::Text("     CAMERA %d", cam);
	}
	else {
		ImGui::Text("     PLAYER %d", cam);
	}
	ImGui::PopStyleColor();
	ImGui::PopFont();	
	ImGui::End();

	// VENTANA CAMARAS

	ImVec2 windowSizeBottom = ImVec2(950.f, 100.0f); 
	ImVec2 windowPosBottom = ImVec2((screenSize.x - windowSizeBottom.x) / 2, screenSize.y - 100.f); 

	ImGui::SetNextWindowPos(windowPosBottom, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSizeBottom, ImGuiCond_Always);
	ImGui::Begin("Cameras Circuit", nullptr, flags);

	ImGui::PushFont(font4);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255.0f, 255.0f, 255.0f, 1.0f));
	ImGui::SeparatorText("CAMERES CIRCUIT");
	ImGui::PopStyleColor();
	ImGui::PopFont();
	//ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, buttonRounding);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	for (int i = 0; i < 12; ++i) {
		char buf[32];
		sprintf_s(buf, "%d", i + 1);
		if (ImGui::Button(buf, ImVec2(65.f, 50.f))) {
			camera.setType(i + 3);
			camera.setFlagPlayer(0);
		}
		if (i < 11) ImGui::SameLine();
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::End();
	font4->Scale = backup;

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}

void Game::velocityUI()
{

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoBackground;

	ImVec2 screenSize = ImGui::GetIO().DisplaySize;

	char speedText[50];
	snprintf(speedText, sizeof(speedText), "%.2f Km/h", this->velocity * (-12));

	// Calcula el tamaño y la posición de la ventana basado en el tamaño de la pantalla y los márgenes deseados
	const ImVec2 margin = ImVec2(40, 40);  // Margen de 40 píxeles por cada lado
	const ImVec2 window_pos = ImVec2(screenSize.x - margin.x, screenSize.y - margin.x);
	const ImVec2 window_size = ImVec2(0, 0);  // El tamaño se ajusta automáticamente basado en el contenido

	// Empieza un nuevo frame para ImGui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Configura la posición y el tamaño de la próxima ventana (la ventana de velocidad)
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, ImVec2(1.0f, 1.0f));  // Anclado a la esquina inferior derecha
	ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

	ImGui::Begin("Velocidad", nullptr, flags);
	ImGui::PushFont(font3); // Utiliza la fuente 'font3' para el siguiente texto

	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("VELOCITY").x) / 2);
	ImGui::Text("VELOCITY");

	// Centra el texto "150km/h" en la ventana
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("150km/h").x) / 2);
	ImGui::Text("%s", speedText);  // Texto de la velocidad centrado

	// Restauramos la fuente por defecto para el resto de la interfaz
	ImGui::PopFont();

	// Termina la ventana
	ImGui::End();

	// Renderiza el frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}

float clamp(float value, float min, float max) {
	return (value < min) ? min : (value > max) ? max : value;
}

void Game::mapUI() {

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoBackground;

	ImVec2 screenSize = ImGui::GetIO().DisplaySize;

	// Calcula el tamaño y la posición de la ventana basado en el tamaño de la pantalla y los márgenes deseados
	const ImVec2 margin = ImVec2(40, 40);  // Margen de 40 píxeles por cada lado
	const ImVec2 window_pos = ImVec2(0.0f + margin.x, screenSize.y - 200 - margin.x);
	const ImVec2 window_size = ImVec2(0, 0);  // El tamaño se ajusta automáticamente basado en el contenido

	// Empieza un nuevo frame para ImGui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Configura la posición y el tamaño de la próxima ventana (la ventana de velocidad)
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, ImVec2(0.0f, 0.0f));  // Anclado a la esquina inferior derecha
	ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

	int imageWidth, imageHeight, imageChannels;
	unsigned char* imageData = stbi_load("images/mask3.png", &imageWidth, &imageHeight, &imageChannels, 0);

	if (imageData) {
		// Assuming you've created an ImGui window
		ImGui::Begin("Map", nullptr, flags);

		// Create an ImGui texture from the loaded image data
		ImGui::Image((void*)9, ImVec2(200, 200));

		float startX = 5.0f + 100;
		float startY = screenSize.y - 200 + 100;

		float endX = 499 * 2;
		float endY = 196 * 2;

		glm::vec3 position = models[1]->getMeshes()[0]->getPosition();


		float moveX = clamp(998 * ((position.x + 246) / 498), 0, 998); // 0 - 998
		float moveY = clamp(385 * ((position.z + 95) / 194), 0, 385); // 0 - 385

		ImGui::GetWindowDrawList()->AddImage(
			(void*)(intptr_t)12,
			ImVec2(0.0f, 0.0f),
			ImVec2(screenSize.x, screenSize.y)
		);

		ImGui::GetWindowDrawList()->AddImage(
			(void*)(intptr_t)10,
			ImVec2(startX - moveX + margin.x,
				startY - moveY - margin.x),
			ImVec2(startX + endX - moveX + margin.x,
				startY + endY - moveY - margin.x)
		);

		ImGui::GetWindowDrawList()->AddImage(
			(void*)(intptr_t)11,
			ImVec2(startX + 15, startY - 60),
			ImVec2(startX + 50 + 15, startY + 50 - 60)
		);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		stbi_image_free(imageData); // Free the image data when done
	}
	// Renderiza el frame

	ImGui::EndFrame();

}

void Game::timeUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoBackground;

	ImVec2 screenSize = ImGui::GetIO().DisplaySize;

	// Usar Chrono para medir el tiempo
	//static 
	//startTime = std::chrono::steady_clock::now();
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = currentTime - startTime;

	// Convertir el tiempo a segundos y minutos
	float timeInSeconds = elapsed.count();
	int minutes = static_cast<int>(timeInSeconds / 60);
	float seconds = timeInSeconds - (minutes * 60);

	// Configuración de la ventana ImGui
	const ImVec2 window_pos = ImVec2(screenSize.x - 40.f, 50.f);
	const ImVec2 window_size = ImVec2(0, 0);  // El tamaño se ajusta automáticamente basado en el contenido

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, ImVec2(1.0f, 1.0f));
	ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

	ImGui::Begin("Time", nullptr, flags);
	ImGui::PushFont(font3);

	// Mostrar el tiempo
	if (minutes > 0) {
		ImGui::Text("%d:%05.2f s", minutes, seconds);
	}
	else {
		ImGui::Text("%.2f s", seconds);
	}

	ImGui::PopFont();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}

void Game::lapUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoBackground;

	ImVec2 screenSize = ImGui::GetIO().DisplaySize;

	// Configuración de la ventana ImGui
	const ImVec2 window_pos = ImVec2(150.f, 50.f);
	const ImVec2 window_size = ImVec2(0, 0);  // El tamaño se ajusta automáticamente basado en el contenido

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, ImVec2(1.0f, 1.0f));
	ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

	ImGui::Begin("Lap", nullptr, flags);
	ImGui::PushFont(font3);

	ImGui::Text("%d / 3", lap);

	ImGui::PopFont();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}

void Game::countDownUI(bool &flag)
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse  |
		ImGuiWindowFlags_NoBackground;


	// Usar Chrono para medir el tiempo
	//startTime2 = std::chrono::steady_clock::now();
	auto currentTime2 = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed2 = currentTime2 - startTime2;
	const float totalDuration = 4.0f;
	float timeRemaining = totalDuration - elapsed2.count();
	if (timeRemaining <= 0.0f) {
		timeRemaining = 0.0f;
		startRaceTimer();
		flag = true;
	}
	int seconds = static_cast<int>(timeRemaining) % 60;

	ImVec2 screenSize = ImGui::GetIO().DisplaySize;
	const ImVec2 window_size = ImVec2(300, 400); 
	const ImVec2 window_pos = ImVec2((screenSize.x + window_size.x) * 0.5f, (screenSize.y + window_size.y) * 0.5f);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, ImVec2(1.0f, 1.0f));
	ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

	ImGui::Begin("Time", nullptr, flags);
	ImGui::PushFont(font4);

	const char* title = "X";
	ImVec2 textSize = ImGui::CalcTextSize(title);
	ImGui::SetCursorPosX((window_size.x - textSize.x) * 0.5f);
	ImGui::Text("%d", seconds);

	ImGui::PopFont();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}


// ===============================================================
// Functions =====================================================
// ===============================================================

void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;

	/*this->start = clock::now();
	this->end = clock::now();
	std::chrono::duration<float> elapsed_seconds = end - start;
	this->dt = elapsed_seconds.count();

	std::cout << "Delta time: " << this-dt << "segundos " << std::endl;*/
}

void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Calc offset
	this->mouseOffsetX = (this->mouseX - this->lastMouseX) * 10;
	this->mouseOffsetY = (this->lastMouseY - this->mouseY) * 10;

	//Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

	//Move light
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		this->pointLights[0]->setPosition(this->camera.getPosition());
	}
}

void Game::updateKeyboardInput()
{
	//Program
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//glfwSetWindowShouldClose(this->window, GLFW_TRUE);
		saveGameStates();
		gameStates.clear();
		reset();

	}
	if (velocity < 0) {
		velocity -= friction_coefficient * velocity * dt;
	}
	else if (velocity > 0) {
		velocity += friction_coefficient * velocity * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		velocity += engineForce * 0.005 * dt;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS && velocity > 0)
	{
		velocity -= engineForce * 0.4f * 0.005 * dt;
		if (velocity < 0)
		{
			velocity = 0;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		velocity -= engineForce * 0.005 * dt;
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS && velocity < 0)
	{
		velocity += engineForce * 0.4f * 0.005 * dt;
		if (velocity > 0)
		{
			velocity = 0;
		}
	}

	if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		// Girar a la derecha
		if (velocity != 0) {
			velocidadRotacion -= 0.2f * std::min(abs(velocidadRotacion / 0.65f) + 0.05f, 1.f) * dt * 144.f;
			velocidadRotacion = -1.f * std::min(abs(velocidadRotacion), 0.65f);
		}
	}
	else if (glfwGetKey(this->window, GLFW_KEY_RIGHT) != GLFW_PRESS && velocidadRotacion < 0) {
		// Girar a la izquierda
		velocidadRotacion = 0.f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		// Girar a la izquierda
		if (velocity != 0) {
			velocidadRotacion += 0.2f * std::min(abs(velocidadRotacion / 0.65f) + 0.05f, 1.f) * dt * 144.f;
			velocidadRotacion = std::min(velocidadRotacion, 0.65f);
		}
	}
	else if (glfwGetKey(this->window, GLFW_KEY_LEFT) != GLFW_PRESS && velocidadRotacion > 0) {
		// Girar a la izquierda
		velocidadRotacion = 0.f;
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		if (camera.getType() != 1)
			camera.setType(1);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		if (camera.getType() != 0)
			camera.setType(0);
	}

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		if (camera.getType() == 0)
			camera.setType(1);
		else
			camera.setType(0);
	}

	//Camera
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera.move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.move(this->dt, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.move(this->dt, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.move(this->dt, RIGHT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS) // Tecla E para subir
	{
		this->camera.move(this->dt, UP);
	}
	if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS) // Tecla Q para bajar
	{
		this->camera.move(this->dt, DOWN);
	}
	if (glfwGetKey(this->window, GLFW_KEY_Z) == GLFW_PRESS) // Tecla Z para girar a la izquierda
	{
		this->camera.move(this->dt, TURN_LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_X) == GLFW_PRESS) // Tecla X para girar a la derecha
	{
		this->camera.move(this->dt, TURN_RIGHT);
	}
}

void Game::updateInput()
{
	glfwPollEvents();

	this->updateKeyboardInput();
	this->updateMouseInput();
	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

// ===============================================================
// PlayMode ======================================================
// ===============================================================

std::string vec3ToString(const glm::vec3& vec) {
	return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")";
}

/*namespace boost {
	namespace serialization {

		template<class Archive>
		void save(Archive& ar, std::vector<GameState>& vec, const unsigned int version) {
			unsigned int size = static_cast<unsigned int>(vec.size());
			ar& size; // Serialize the size first

			for (size_t i = 0; i < vec.size(); ++i) {
				ar& vec[i]; // Serialize individual GameState objects
			}
		}

		template<class Archive>
		void load(Archive& ar, std::vector<GameState>& vec, const unsigned int version) {
			unsigned int size;
			ar& size; // Deserialize the size first

			vec.resize(size); // Resize the vector to accommodate the elements

			for (size_t i = 0; i < size; ++i) {
				ar& vec[i]; // Deserialize individual GameState objects
			}
		}

	} // namespace serialization
} // namespace boost */

int frame = 0;

void Game::updatePlay()
{

	/*std::cout << "Coordenadas: (" << camera.getPosition().x << ", " 
		<< camera.getPosition().y << ", " << camera.getPosition().z << ")" << std::endl;
	std::cout << "Yaw: " << camera.getYaw() << std::endl;*/
	//UPDATE INPUT ---
	this->updateDt();
	this->updateInput();

	//camera.setType(0); //THIRD

	//velocity += acceleration;
	if (velocity >= maxVelocity / 2) {
		velocity = maxVelocity / 2;
	}
	else if (velocity <= -maxVelocity) {
		velocity = -maxVelocity;
	}

	/*if (velocidadRotacion >= velocidadRotacionMaxima) {
		velocidadRotacion = velocidadRotacionMaxima;
	}
	else if (velocidadRotacion <= -velocidadRotacionMaxima) {
		velocidadRotacion = -velocidadRotacionMaxima;
	}*/

	if (startTimeStatus) {
		gameStates.push_back(GameState(dt, 
			glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS, 
			glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS, 
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS, 
			glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS));
		/*if (gameStates.size() >= 2000) {
			saveGameStates();
			gameStates.clear();
		}*/
	}

	frame++;

	// Aplica la rotación
	if (velocidadRotacion != 0.f) {
		float velocityAbs = std::abs(velocity) / 0.04f;
		models[1]->getMeshes()[0]->rotate(velocidadRotacion * std::min(velocityAbs, 1.0f) * 200.f * dt, glm::vec3(0, 1, 0)); // * dt
	}

	glm::vec3 forwardDirection = glm::rotate(models[1]->getMeshes()[0]->getRotation(), glm::vec3(0, 0, -1));
	glm::vec3 movement = forwardDirection * (float(velocity));
	models[1]->getMeshes()[0]->move(movement * 250.f * dt); // * dt

	glm::vec3 modelPosition = models[1]->getMeshes()[0]->getPosition();
	glm::quat modelRotation = models[1]->getMeshes()[0]->getRotation();

	glm::vec3 cameraOffset, newCameraPosition, backwardDirection;
	if (camera.getType() == 0) { //THIRD
		backwardDirection = glm::rotate(modelRotation, glm::vec3(0.0f, 0.0f, 1.0f));
		cameraOffset = backwardDirection * -2.f;
		cameraOffset.y += 1.f;
		newCameraPosition = modelPosition + cameraOffset;

		camera.setFront(glm::normalize(modelPosition - newCameraPosition));
	}
	else { //FIRST
		forwardDirection = glm::rotate(modelRotation, glm::vec3(0, 0, 1));
		cameraOffset = glm::vec3(0.0f, 0.2f, 0.0f); 
		newCameraPosition = modelPosition + cameraOffset;
		camera.setFront(forwardDirection);
	}

	camera.setPosition(newCameraPosition);

	//CHECKPOINT
	Checkpoint* actCheck = checkpoints[aux];
	if (actCheck->passed(models[1]->getMeshes()[0]->getPosition())) {
		aux++;
		checkpointsPassed++;
		if (aux == 20)
			aux %= 20;
		if (checkpointsPassed % 20 == 0)
			lap++;
	}

	if (lap == 4)
	{
		saveGameStates();
		gameStates.clear();
		reset();
	}
	
}

void Game::updateView()
{
	std::cout << frame << std::endl;
	if (frame < gameStates.size()) {
		std::cout << gameStates[frame].dt << gameStates[frame].up << gameStates[frame].down << gameStates[frame].right << gameStates[frame].left << std::endl;
		//this->updateDt();
		dt = gameStates[frame].dt;
		if (velocity < 0) {
			velocity -= friction_coefficient * velocity * dt;
		}
		else if (velocity > 0) {
			velocity += friction_coefficient * velocity * dt;
		}
		if (gameStates[frame].down) {
			velocity += engineForce * 0.005 * dt;
		}
		else if (!gameStates[frame].down && velocity > 0)
		{
			velocity -= engineForce * 0.4f * 0.005 * dt;
			if (velocity < 0)
			{
				velocity = 0;
			}
		}
		if (gameStates[frame].up) {
			velocity -= engineForce * 0.005 * dt;
		}
		else if (!gameStates[frame].up && velocity < 0)
		{
			velocity += engineForce * 0.4f * 0.005 * dt;
			if (velocity > 0)
			{
				velocity = 0;
			}
		}
		if (gameStates[frame].right) {
			if (velocity != 0) {
				velocidadRotacion -= 0.2f * std::min(abs(velocidadRotacion / 0.65f) + 0.05f, 1.f) * dt * 144.f;
				velocidadRotacion = -1.f * std::min(abs(velocidadRotacion), 0.65f);
			}
		}
		else if (!gameStates[frame].right && velocidadRotacion < 0) {
			velocidadRotacion = 0.f;
		}
		if (gameStates[frame].left) {
			if (velocity != 0) {
				velocidadRotacion += 0.2f * std::min(abs(velocidadRotacion / 0.65f) + 0.05f, 1.f) * dt * 144.f;
				velocidadRotacion = std::min(velocidadRotacion, 0.65f);
			}
		}
		else if (!gameStates[frame].left && velocidadRotacion > 0) {
			velocidadRotacion = 0.f;
		}
		frame++;
	}

	std::cout << "Coordenadas: (" << models[1]->getMeshes()[0]->getPosition().x << ", "
		<< models[1]->getMeshes()[0]->getPosition().y << ", " << models[1]->getMeshes()[0]->getPosition().z << ")" << std::endl;

	if (velocity >= maxVelocity / 2) {
		velocity =  maxVelocity / 2;
	}
	else if (velocity <= -maxVelocity) {
		velocity = -maxVelocity;
	}

	/*if (velocidadRotacion >= velocidadRotacionMaxima) {
		velocidadRotacion = velocidadRotacionMaxima;
	}
	else if (velocidadRotacion <= -velocidadRotacionMaxima) {
		velocidadRotacion = -velocidadRotacionMaxima;
	}*/

	// Aplica la rotación
	if (velocidadRotacion != 0.f) {
		float velocityAbs = std::abs(velocity) / 0.04f;
		models[1]->getMeshes()[0]->rotate(velocidadRotacion * std::min(velocityAbs, 1.0f) * 200.f * dt, glm::vec3(0, 1, 0)); // * dt
	}

	glm::vec3 forwardDirection = glm::rotate(models[1]->getMeshes()[0]->getRotation(), glm::vec3(0, 0, -1));
	glm::vec3 movement = forwardDirection * (float(velocity));
	models[1]->getMeshes()[0]->move(movement * 250.f * dt); // * dt

	glm::vec3 modelPosition = models[1]->getMeshes()[0]->getPosition();
	glm::quat modelRotation = models[1]->getMeshes()[0]->getRotation();

	glm::vec3 cameraOffset, newCameraPosition, backwardDirection;
	if (camera.getType() == 0) { //THIRD
		backwardDirection = glm::rotate(modelRotation, glm::vec3(0.0f, 0.0f, 1.0f));
		cameraOffset = backwardDirection * -2.f;
		cameraOffset.y += 1.f;
		newCameraPosition = modelPosition + cameraOffset;

		camera.setFront(glm::normalize(modelPosition - newCameraPosition));
	}
	else { //FIRST
		forwardDirection = glm::rotate(modelRotation, glm::vec3(0, 0, 1));
		cameraOffset = glm::vec3(0.0f, 0.2f, 0.0f);
		newCameraPosition = modelPosition + cameraOffset;
		camera.setFront(forwardDirection);
	}

	camera.setPosition(newCameraPosition);

}

void Game::saveGameStates() {
	std::string filename = saveFile;
	std::cout << filename << std::endl;

	// Check if the file exists
	if (!boost::filesystem::exists(filename)) {
		std::ofstream createFile(filename);
		createFile.close();
	}

	std::ofstream outFile(filename, std::ios::app);

	if (outFile.is_open()) {
		boost::archive::text_oarchive oa(outFile);
		oa << gameStates;
		outFile.close();
	}
	else {
		std::cerr << "Unable to open file!" << std::endl;
	}
}

void Game::clearFile(const std::string& filename) {
	std::ofstream outFile(filename, std::ios::trunc);

	if (outFile.is_open()) {
		outFile.close();
		std::cout << "File '" << filename << "' cleared." << std::endl;
	}
	else {
		std::cerr << "Unable to open file '" << filename << "'!" << std::endl;
	}
}

void Game::loadGameStates() {
	std::ifstream inFile("gamestates_2023_12_16_160654.txt");

	if (inFile.is_open()) {
		try {
			boost::archive::text_iarchive ia(inFile);
			ia >> gameStates;
			inFile.close();
			std::cout << "Game states loaded successfully. Size: " << gameStates.size() << std::endl;
		}
		catch (const boost::archive::archive_exception& e) {
			std::cerr << "Exception during deserialization: " << e.what() << std::endl;
		}
		catch (const std::exception& ex) {
			std::cerr << "Exception: " << ex.what() << std::endl;
		}
	}
	else {
		std::cerr << "Unable to open file!" << std::endl;
	}
}

void Game::renderPlay()
{
	//UPDATE --- 
	//updateInput(window);

	//DRAW ---
	//Clear
	glClearColor(0.52f, 0.83f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Update the uniforms
	this->updateUniforms();

	//Render models
	for (auto& i : this->models)
		i->render(this->shaders[SHADER_CORE_PROGRAM]);

	//this->meshes[0]->render(this->shaders[SHADER_CORE_PROGRAM]);

	//End Draw
	//glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

// ===============================================================
// ViewMode ======================================================
// ===============================================================

void Game::camerasPlayers(int player, int typeCam)
{
	glm::vec3 cameraPos;
	glm::vec3 cameraOffset, newCameraPosition, backwardDirection;
	glm::vec3 forwardDirection = glm::rotate(models[1]->getMeshes()[0]->getRotation(), glm::vec3(0, 0, -1));
	glm::vec3 modelPosition = models[1]->getMeshes()[0]->getPosition();
	glm::quat modelRotation = models[1]->getMeshes()[0]->getRotation();


	switch (player)
	{
	case PLAYER_1:
		if (typeCam == 0) { //THIRD
			backwardDirection = glm::rotate(modelRotation, glm::vec3(0.0f, 0.0f, 1.0f));
			cameraOffset = backwardDirection * -2.f;
			cameraOffset.y += 1.f;
			newCameraPosition = modelPosition + cameraOffset;

			camera.setFront(glm::normalize(modelPosition - newCameraPosition));
		}
		if (typeCam == 1) { //FIRST
			forwardDirection = glm::rotate(modelRotation, glm::vec3(0, 0, 1));
			cameraOffset = glm::vec3(0.0f, 0.2f, 0.0f);
			newCameraPosition = modelPosition + cameraOffset;
			camera.setFront(forwardDirection);
		}
		break;
	case PLAYER_2:
		cameraPos = camera.getCameraPosition(CAMERA_2 - 2);
		camera.setYaw(-90.f);
		break;
	case PLAYER_3:
		cameraPos = camera.getCameraPosition(CAMERA_3 - 2);
		camera.setYaw(-80.f);
		break;
	case PLAYER_4:
		cameraPos = camera.getCameraPosition(CAMERA_4 - 2);
		camera.setYaw(-25.f);
		break;
	case PLAYER_5:
		cameraPos = camera.getCameraPosition(CAMERA_5 - 2);
		camera.setYaw(170.f);
		break;
	}

	camera.setPosition(newCameraPosition);
}

void Game::camerasCircuit(int typeCam)
{
	glm::vec3 cameraPos;
	camera.setPitch(-10.f);

	switch (typeCam)
	{
	case CAMERA_1:
		camera.setType(CAMERA_1);
		cameraPos = camera.getCameraPosition(CAMERA_1 - 2);
		camera.setYaw(155.f);
		break;
	case CAMERA_2:
		camera.setType(CAMERA_2);
		cameraPos = camera.getCameraPosition(CAMERA_2 - 2);
		camera.setYaw(-90.f);
		break;
	case CAMERA_3:
		camera.setType(CAMERA_3);
		cameraPos = camera.getCameraPosition(CAMERA_3 - 2);
		camera.setYaw(-80.f);
		break;
	case CAMERA_4:
		camera.setType(CAMERA_4);
		cameraPos = camera.getCameraPosition(CAMERA_4 - 2);
		camera.setYaw(-25.f);
		break;
	case CAMERA_5:
		camera.setType(CAMERA_5);
		cameraPos = camera.getCameraPosition(CAMERA_5 - 2);
		camera.setYaw(170.f);
		break;
	case CAMERA_6:
		camera.setType(CAMERA_6);
		cameraPos = camera.getCameraPosition(CAMERA_6 - 2);
		camera.setYaw(15.f);
		break;
	case CAMERA_7:
		camera.setType(CAMERA_7);
		cameraPos = camera.getCameraPosition(CAMERA_7 - 2);
		camera.setYaw(-72.f);
		break;
	case CAMERA_8:
		camera.setType(CAMERA_8);
		cameraPos = camera.getCameraPosition(CAMERA_8 - 2);
		camera.setYaw(0.f);
		break;
	case CAMERA_9:
		camera.setType(CAMERA_9);
		cameraPos = camera.getCameraPosition(CAMERA_9 - 2);
		camera.setYaw(30.f);
		break;
	case CAMERA_10:
		camera.setType(CAMERA_10);
		cameraPos = camera.getCameraPosition(CAMERA_10 - 2);
		camera.setYaw(250.f);
		break;
	case CAMERA_11:
		camera.setType(CAMERA_11);
		cameraPos = camera.getCameraPosition(CAMERA_11 - 2);
		camera.setYaw(70.f);
		break;
	case CAMERA_12:
		camera.setType(CAMERA_12);
		cameraPos = camera.getCameraPosition(CAMERA_12 - 2);
		camera.setYaw(158.f);
		break;
	default:
		break;
	}

	camera.setPosition(cameraPos);
}

void Game::specialCams(int typeCam)
{
	glm::vec3 cameraPos;
	switch (typeCam)
	{
	case PANORAMICA:
		camera.setType(PANORAMICA);
		cameraPos = camera.getCameraPosition(PANORAMICA - 2);
		camera.setYaw(150.f);
		camera.setPitch(-30.f);
		break;
	}

	camera.setPosition(cameraPos); 
}

void Game::updateViewCams()
{
	//Program
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//glfwSetWindowShouldClose(this->window, GLFW_TRUE);
		reset();
	}

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;

	int typeCam = camera.getType();
	int playerCam = camera.getFlagPlayer();


	if (playerCam == 1) //PLAYER
	{
		camerasPlayers(camera.getPlayer(), camera.getCamPlayer());
	}
	else if (typeCam >= 3 && typeCam <= 14 && playerCam == 0) //CAMERAS CIRCUIT
	{
		camerasCircuit(typeCam);
	}
	else {
		specialCams(typeCam);
	}
}

void Game::renderView()
{
	//UPDATE --- 
	//updateInput(window);

	//DRAW ---
	//Clear
	glClearColor(0.52f, 0.83f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Update the uniforms
	this->updateUniforms();

	//Render models
	for (auto& i : this->models)
		i->render(this->shaders[SHADER_CORE_PROGRAM]);

	//this->meshes[0]->render(this->shaders[SHADER_CORE_PROGRAM]);

	//End Draw
	//glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::reset() {
	if (startGame != 0)
		startGame = 0;

	// parar el coche
	velocity = 0.0f;
	velocidadRotacion = 0.0f;
	dt = 0.0f;
	curTime = 0.0f;
	lastTime = 0.0f;

	// moverlo al inicio
	models[1]->getMeshes()[0]->setPosition(glm::vec3(-85.f, floor + 0.25, -60.f));
	models[1]->getMeshes()[0]->setRotation(glm::quat(1.f, 0.f, 0.f, 0.f));
	models[1]->getMeshes()[0]->rotate(90, glm::vec3(0, 1, 0));
	// chrono a 0
	startTimeStatus = false;
	startTime2Status = false;
	flag1 = false;
	flag2 = false;

	checkpointsPassed = 0;
	aux = 0;
	lap = 1;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Game::startRaceTimer() {
	startTime = std::chrono::steady_clock::now();
}

void Game::startCountdownTimer() {
	startTime2 = std::chrono::steady_clock::now();
}


// ===============================================================
// Static Functions ==============================================
// ===============================================================

void Game::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
};