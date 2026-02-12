#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include "Camera.h"
#include "Model.h"
#include "Game.cpp"
#include "OmniEngine.h"

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

Game game;
GLFWwindow* window;
Camera* mainCamera;
vector<OmniObject*> hierarchy;

OmniEngine engine;

void OmniEngine::addToHierarchy(OmniObject* object) {
    hierarchy.push_back(object);
}
void OmniEngine::setMainCamera(Camera* camera) {
	mainCamera = camera;
}
int OmniEngine::getKeyboardInput(int key) {
    return glfwGetKey(window, key);
}
glm::vec2 OmniEngine::getMousePosition() {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return glm::vec2(xpos, ypos);
}
glm::vec2 OmniEngine::getScreenSize() {
    return glm::vec2(SCR_WIDTH, SCR_HEIGHT);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	mainCamera->aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;
}

//mainCamera = Camera(glm::vec3(0, 0, 3), glm::vec3(1), glm::vec3(0, -90, 0));

float lastFrame = 0.0f;
void processUpdate(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float deltaTime = 0.0f;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
	std::cout << 1/deltaTime << std::endl;
    game.update(deltaTime);
}

float vertices[] = {
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f,  // top right front
     0.5f, -0.5f, 0.0f,     1.0f, 0.0f,  // bottom right front
    -0.5f, -0.5f, 0.0f,     1.0f, 1.0f,  // bottom left front
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f,  // top left front
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3,    // second triangle
};
int main() {
	// Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    stbi_set_flip_vertically_on_load(true);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OmniEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(0); // Disable V-Sync
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Capture the mouse
    
    glEnable(GL_DEPTH_TEST);

    Shader mainShader("C:/Users/donot/source/repos/OmniEngine/OmniEngine/vertex.vs", "C:/Users/donot/source/repos/OmniEngine/OmniEngine/fragment.fs");

	Model ourModel("C:/Users/donot/Downloads/backpack/backpack.obj");
	ourModel.rotation = glm::vec3(0, 45, 45);

    game.init(engine);
    mainCamera->aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
		processUpdate(window);

		// Rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode

        mainShader.use();

        mainShader.setMat4("view", mainCamera->getViewMatrix());
        mainShader.setMat4("projection", mainCamera->getProjectionMatrix());

        for (int i = 0; i < hierarchy.size(); i++) {
            hierarchy[i]->update(0);
		}
		ourModel.Draw(mainShader);

		// Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}