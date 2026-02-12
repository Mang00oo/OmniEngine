#include "OmniEngine.h"
#include <GLFW/glfw3.h>

class Game {
public:
	void init(OmniEngine _engine) {
		_engine = engine;
		mainCamera = new Camera(glm::vec3(0, 0, 8), glm::vec3(1), glm::vec3(0, -90, 0));
		engine.setMainCamera(mainCamera);
	}
	void update(float dt) {
		// Camera movement
		const float cameraSpeed = 2.5f * dt; // adjust accordingly
		glm::vec3 cameraDirection = mainCamera->getDirection();
		if (engine.getKeyboardInput(GLFW_KEY_W) == GLFW_PRESS)
			mainCamera->position -= cameraSpeed * -cameraDirection;
		if (engine.getKeyboardInput(GLFW_KEY_S) == GLFW_PRESS)
			mainCamera->position += cameraSpeed * -cameraDirection;
		if (engine.getKeyboardInput(GLFW_KEY_A) == GLFW_PRESS)
			mainCamera->position -= glm::normalize(glm::cross(cameraDirection, glm::vec3(0, 1, 0))) * cameraSpeed;
		if (engine.getKeyboardInput(GLFW_KEY_D) == GLFW_PRESS)
			mainCamera->position += glm::normalize(glm::cross(cameraDirection, glm::vec3(0, 1, 0))) * cameraSpeed;

		// Camera rotation
		float xpos = engine.getMousePosition().x;
		float ypos = engine.getMousePosition().y;
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
		mainCamera->rotation.y += xoffset;
		mainCamera->rotation.x += yoffset;
		if (mainCamera->rotation.x > 89.0f)
			mainCamera->rotation.x = 89.0f;
		if (mainCamera->rotation.x < -89.0f)
			mainCamera->rotation.x = -89.0f;
	}
private:
	OmniEngine engine;
	Camera* mainCamera;

	float lastX = engine.getScreenSize().x / 2, lastY = engine.getScreenSize().y / 2;
	bool firstMouse = true;
};