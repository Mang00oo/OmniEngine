#ifndef OMNIOBJECT_H
#define OMNIOBJECT_H

#include <glm/glm.hpp>
#include <vector>

class OmniObject {
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	OmniObject *parent;
	std::vector<OmniObject*> children;
	OmniObject(glm::vec3 _position = glm::vec3(0), glm::vec3 _scale = glm::vec3(0), glm::vec3 _rotation = glm::vec3(0)) : position(_position), scale(_scale), rotation(_rotation) { spawn(); }
	virtual void update(float dt) {

	}
	virtual void spawn() {

	}
    void setParent(OmniObject* _parent) {
		parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());
		parent = _parent;
		_parent->children.push_back(this);
	}
	glm::vec3 getWorldPosition() {
		if (parent) {
			glm::vec3 parentPosition;
			parentPosition = parent->getWorldPosition();
			return parentPosition + position;
		}
		else {
			return position;
		}
	}
protected:
	
};

#endif