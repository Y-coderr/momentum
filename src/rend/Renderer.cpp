#include "Renderer.hpp"
#include <Eigen/Dense>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imGui/imgui.h"
#include "imGui/imgui_impl_opengl3.h"
#include "imGui/imgui_impl_glfw.h"

//debug
#include <iostream>

constexpr int WIN_SIZE[2] = { 1920,1080 };
constexpr int INITIAL_TRANFORM_SSBO_SIZE = 10, FLOATS_PER_MATRIX4 = 16;



float Timer() {
	static double lastTime = 0.0;
	double currtime = glfwGetTime();
	float dt = float(currtime - lastTime);
	lastTime = currtime;
	return dt;
}

void Renderer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	if (renderer && renderer->e_cam) {
		renderer->e_cam->setScrollDelta(static_cast<float>(yoffset));
	}
}

void Renderer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	if (renderer) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
			renderer->playbar.Simulate = !renderer->playbar.Simulate;
		}
		if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
			renderer->playbar.Move = !renderer->playbar.Move;
		}
	}
}

void Renderer::imGuiInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

}

void Renderer::imGuiDraw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpaceOverViewport(dockspace_id, ImGui::GetMainViewport());

}

void Renderer::imGuiRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// --- Multi-Viewport Support ---
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void Renderer::setupBuffers()
{
	glGenVertexArrays(1, &CUBE_SHAPE_VAO);
	glBindVertexArray(CUBE_SHAPE_VAO);
	glGenBuffers(1, &CUBE_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, CUBE_VBO);
	glBufferData(GL_ARRAY_BUFFER, library->Cube_shape_vertex->getSizeofShapeVertex(), library->Cube_shape_vertex->vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(myVec3), nullptr);
	glGenBuffers(1, &CUBE_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CUBE_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, library->Cube_shape_vertex->getSizeofShapeIndices(), library->Cube_shape_vertex->indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	glGenVertexArrays(1, &SPHERE_SHAPE_VAO);
	glBindVertexArray(SPHERE_SHAPE_VAO);
	glGenBuffers(1, &SPHERE_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, SPHERE_VBO);
	glBufferData(GL_ARRAY_BUFFER, library->Sphere_shape_vertex->getSizeofShapeVertex(), library->Sphere_shape_vertex->vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(myVec3), nullptr);
	glGenBuffers(1, &SPHERE_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SPHERE_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, library->Sphere_shape_vertex->getSizeofShapeIndices(), library->Sphere_shape_vertex->indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}


Renderer::Renderer(std::shared_ptr<std::vector<std::unique_ptr<Body>>> Ent) : Entities(Ent)
{
    library = new MeshLibrary();
    library->Cube_shape_vertex = std::make_unique<Mesh>(Mesh::createCUBE());
    library->Sphere_shape_vertex = std::make_unique<Mesh>(Mesh::createSPHERE());
    library->INDICES_COUNT_CUBE = library->Cube_shape_vertex->indices.size();
    library->INDICES_COUNT_SPHERE = library->Sphere_shape_vertex->indices.size();
    
    std::cout << "Initializing GLFW..." << std::endl;
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    std::cout << "Creating window..." << std::endl;
    window = glfwCreateWindow(WIN_SIZE[0], WIN_SIZE[1], "momentum", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    // Initialize GLFW with more compatible OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    std::cout << "Creating window..." << std::endl;
    window = glfwCreateWindow(WIN_SIZE[0], WIN_SIZE[1], "momentum", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    
    std::cout << "Loading GLAD..." << std::endl;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WIN_SIZE[0], WIN_SIZE[1]);


	//this func gives access to renderer class to glfw
	glfwSetWindowUserPointer(window, this);

	library = new MeshLibrary();

	imGuiInit();

	playbar.Simulate = false;
	playbar.Move = true;
}

Renderer::~Renderer()
{

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();



	if (library != nullptr) {
		delete library;
		library = nullptr;
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Renderer::run(std::function<void(float)> engineUpdate, std::function <void()>engineUi)
{
	glfwSetScrollCallback(window,Renderer::scroll_callback);
	glfwSetKeyCallback(window, Renderer::key_callback);

	e_shader = std::make_unique<Shader>("../src/rend/shaders/basic.vert","../src/rend/shaders/basic.frag");
	e_shader->Activate();


	if (library->Cube_shape_vertex == nullptr)exit(2);
	if (library->Sphere_shape_vertex == nullptr)exit(2);

	setupBuffers();
	

	e_cam = std::make_unique<ArcBall>(45, 0.1f, 100.f, ((float)WIN_SIZE[0] / (float)WIN_SIZE[1]));
	while (!glfwWindowShouldClose(window)) 
	{
		deltaTime = Timer();
		imGuiDraw();

		if (playbar.Simulate) {
			engineUpdate(deltaTime); 
		}
		else {
			engineUi();
		}
		if (playbar.Move) {
			e_cam->Update(window);
			e_shader->upload2GPU(VIEW, e_cam->renderView());
			e_shader->upload2GPU(PERS, e_cam->getProjMatrix());
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		imGuiRender();
		for (auto& entity : *Entities) {
			e_shader->upload2GPU(MODEL, entity->ConstructTransformMat());
			if (entity->Collider == CUBE) {
				glBindVertexArray(CUBE_SHAPE_VAO);
				glDrawElements(GL_TRIANGLES, library->INDICES_COUNT_CUBE, GL_UNSIGNED_INT, nullptr);
			}
			else {
				glBindVertexArray(SPHERE_SHAPE_VAO);
				glDrawElements(GL_TRIANGLES, library->INDICES_COUNT_SPHERE, GL_UNSIGNED_INT, nullptr);
			}
		}

		

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}
