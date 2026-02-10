#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.cpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.cpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Model.cpp"

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

Camera mainCamera = Camera(glm::vec3(0, 0, 3), glm::vec3(1), glm::vec3(0, -90, 0));
glm::vec3 cameraDirection;

float lastFrame = 0.0f;
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float deltaTime = 0.0f;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
	std::cout << 1/deltaTime << std::endl;
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mainCamera.position -= cameraSpeed * -cameraDirection;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mainCamera.position += cameraSpeed * -cameraDirection;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mainCamera.position -= glm::normalize(glm::cross(cameraDirection, glm::vec3(0, 1, 0))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mainCamera.position += glm::normalize(glm::cross(cameraDirection, glm::vec3(0, 1, 0))) * cameraSpeed;

    cameraDirection.x = cos(glm::radians(mainCamera.rotation.y)) * cos(glm::radians(mainCamera.rotation.x));
    cameraDirection.y = sin(glm::radians(mainCamera.rotation.x));
    cameraDirection.z = sin(glm::radians(mainCamera.rotation.y)) * cos(glm::radians(mainCamera.rotation.x));
}
float lastX = SCR_WIDTH / 2, lastY = SCR_HEIGHT / 2;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
	mainCamera.rotation.y += xoffset;
    mainCamera.rotation.x += yoffset;
    if (mainCamera.rotation.x > 89.0f)
        mainCamera.rotation.x = 89.0f;
    if (mainCamera.rotation.x < -89.0f)
		mainCamera.rotation.x = -89.0f;
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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OmniEngine", NULL, NULL);
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
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glEnable(GL_DEPTH_TEST);

    Shader mainShader("C:/Users/donot/source/repos/OmniEngine/OmniEngine/vertex.vs", "C:/Users/donot/source/repos/OmniEngine/OmniEngine/fragment.fs");

	Model ourModel("C:/Users/donot/Downloads/backpack/backpack.obj");

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
		processInput(window);

		// Rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// Space Transformation
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(mainCamera.position, mainCamera.position + glm::normalize(cameraDirection), glm::vec3(0, 1, 0));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(mainCamera.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        mainShader.use();

        int modelLoc = glGetUniformLocation(mainShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(mainShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(mainShader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		ourModel.Draw(mainShader);

		// Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}