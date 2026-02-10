#include "OmniObject.cpp"

class Camera : public OmniObject {
	public:
		float fov = 90;
		float aspectRatio;
		bool isPerspective = true;
		Camera(glm::vec3 _position = glm::vec3(0), glm::vec3 _scale = glm::vec3(0), glm::vec3 _rotation = glm::vec3(0))
			: OmniObject(_position, _scale, _rotation) {}
		void spawn() override {

		}
		void update(float dt) override {

		}
};