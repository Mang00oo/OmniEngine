#ifndef OMNIENGINE_H
#define OMNIENGINE_H

#include <vector>
#include "OmniObject.h"
#include "Camera.h"
#include "Shader.h"
#include <memory>

class OmniEngine {
	public:
		void addToHierarchy(OmniObject* object);
		void setMainCamera(Camera* camera);
		int getKeyboardInput(int key);
		glm::vec2 getMousePosition();
		glm::vec2 getScreenSize();
		Shader* mainShader;
	private:
};

#endif
