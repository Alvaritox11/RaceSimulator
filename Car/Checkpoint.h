#pragma once
#include "libs.h"

class Checkpoint {
private:
	glm::vec3 tl;
	glm::vec3 tr;
	glm::vec3 bl;
	glm::vec3 br;

	bool activated;
public:

	Checkpoint(const glm::vec3 point) {
		this->tl = point;
		this->tr = point;
		this->bl = point;
		this->br = point;

		this->tl.x -= 6.f;
		this->tl.z += 6.f;
		
		this->tr.x += 6.f;
		this->tr.z += 6.f;

		this->bl.x -= 6.f;
		this->bl.z -= 6.f;

		this->br.x += 6.f;
		this->br.z -= 6.f;

		this->activated = false;
	}	

	bool passed(glm::vec3 position) {
		bool inside_x = position.x >= bl.x && position.x <= br.x;
		bool inside_z = position.z >= bl.z && position.z <= tl.z;

		return inside_x && inside_z;
	}
};