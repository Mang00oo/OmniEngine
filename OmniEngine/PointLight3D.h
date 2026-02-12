#ifndef POINTLIGHT3D_H
#define POINTLIGHT3D_H
#include "OmniObject.h"

class Light : public OmniObject {
	public:
		glm::vec3 color = glm::vec3(1);
		float intensity = 1.0f;
		float range = 10.0f;

		Light(glm::vec3 _position = glm::vec3(0), glm::vec3 _scale = glm::vec3(0), glm::vec3 _rotation = glm::vec3(0))
			: OmniObject(_position, _scale, _rotation) {
		}
		void spawn() override {

		}
		void update(float dt) override {

		}
};
#endif