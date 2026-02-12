#ifndef CAMERA_H
#define CAMERA_H

#include "OmniObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera : public OmniObject {
	public:
		float fov = 90;
		float aspectRatio;
		bool orthographic = false;
		Camera(glm::vec3 _position = glm::vec3(0), glm::vec3 _scale = glm::vec3(0), glm::vec3 _rotation = glm::vec3(0))
			: OmniObject(_position, _scale, _rotation) {}
		glm::vec3 getDirection() {
			glm::vec3 direction;
			direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
			direction.y = sin(glm::radians(rotation.x));
			direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
			return direction;
		}
		glm::mat4 getViewMatrix() {
			return glm::lookAt(position, position + glm::normalize(getDirection()), glm::vec3(0, 1, 0));
		}
		glm::mat4 getProjectionMatrix() {
			if (!orthographic) {
				return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
			}
			else {
				float orthoSize = 10.0f;
				return glm::ortho(-orthoSize * aspectRatio, orthoSize * aspectRatio, -orthoSize, orthoSize, 0.1f, 100.0f);
			}
		}
		void spawn() override {

		}
		void update(float dt) override {

		}
};
#endif