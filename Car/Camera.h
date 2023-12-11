#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc\matrix_transform.hpp>

enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT, UP, DOWN, TURN_LEFT, TURN_RIGHT };

enum cameras { THIRD = 0, FIRST, PANORAMICA, CAMERA_1, CAMERA_2, CAMERA_3, CAMERA_4, CAMERA_5,
	CAMERA_6, CAMERA_7, CAMERA_8, CAMERA_9, CAMERA_10, CAMERA_11, CAMERA_12 };


class Camera
{
private:
	
	glm::mat4 ViewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	int typeCam = 0;
	std::vector<glm::vec3> cameraPositions = {
		glm::vec3(199.0f, 30.0f, -55.0f),  // PANORAMICA
		glm::vec3(162.5f, -2.0f, -65.0f),  // CAMERA_1
		glm::vec3(171.5f, -2.0f, -16.0f),  // CAMERA_2
		glm::vec3(198.0f, -2.0f, 71.3f),   // CAMERA_3
		glm::vec3(73.0f, -2.0f, 73.0f),    // CAMERA_4
		glm::vec3(180.0f, -2.0f, 20.0f),   // CAMERA_5
		glm::vec3(52.0f, -2.0f, -35.0f),   // CAMERA_6
		glm::vec3(17.0f, -2.0f, 60.0f),    // CAMERA_7
		glm::vec3(-110.0f, -2.0f, 17.5f),  // CAMERA_8
		glm::vec3(-190.0f, -2.0f, -28.0f), // CAMERA_9
		glm::vec3(144.0f, -2.0f, 68.0f),   // CAMERA_10
		glm::vec3(-233.0f, -2.0f, 42.0f),  // CAMERA_11
		glm::vec3(-216.5f, -2.0f, -61.5f)  // CAMERA_12
	};


	void updateCameraVectors()
	{
		this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}

	void updateCameraVectorsForThirdPerson() {
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}

	void updateCameraVectorsForPanoramica() {
		
		this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		
		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}

	// Esta es igual al updateCameraVectors(). Quitarla si no hace falta
	void updateCameraVectorsForCircuitCameras() {
		this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}

public:

	// ================================================================
	// Constructor/Destructor =========================================
	// ================================================================

	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
	{
		this->ViewMatrix = glm::mat4(1.f);

		this->movementSpeed = 10.f;
		this->sensitivity = 10.f;

		this->worldUp = worldUp;
		this->position = position;
		this->right = glm::vec3(0.f);
		this->up = worldUp;

		this->pitch = 0.f;
		this->yaw = 90.f;
		this->roll = 0.f;

		this->typeCam = THIRD;

		this->updateCameraVectors();
	}

	~Camera() {}

	// ================================================================
	// Accesors =======================================================
	// ================================================================

	const glm::mat4 getViewMatrix()
	{
		if (typeCam == THIRD) {
			this->updateCameraVectorsForThirdPerson();
		}
		else if (typeCam == FIRST) { 
			this->updateCameraVectorsForThirdPerson();
		}
		else if (typeCam == PANORAMICA) {
			this->updateCameraVectorsForPanoramica();
		}
		else {
			this->updateCameraVectorsForCircuitCameras();
		}

		this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

		return this->ViewMatrix;
	}

	// ================================================================
	// Getters/Setters ================================================
	// ================================================================

	const glm::vec3 getPosition() const { 
		return this->position; 
	}

	void setPosition(const glm::vec3& newPosition) {
		this->position = newPosition;

		/*if (typeCam == THIRD) {
			this->updateCameraVectorsForThirdPerson();
		}
		else if (typeCam == FIRST) {

		}
		else if (typeCam == PANORAMICA) {
			this->updateCameraVectorsForPanoramica();
		}
		else {
			this->updateCameraVectorsForCircuitCameras();
		}*/
		//this->updateCameraVectors();
	}

	void setFront(const glm::vec3& newFront) {
		this->front = glm::normalize(newFront);

		/*if (typeCam == THIRD) {
			this->updateCameraVectorsForThirdPerson();
		}
		else if (typeCam == FIRST) {

		}
		else if (typeCam == PANORAMICA) {
			this->updateCameraVectorsForPanoramica();
		}
		else {
			this->updateCameraVectorsForCircuitCameras();
		}*/
		//this->updateCameraVectors();
	}

	void setType(int type) { this->typeCam = type; }
	int getType() { return typeCam; }
	glm::vec3 getCameraPosition(int position) {
		return cameraPositions[position];
	}
	void setYaw(GLfloat newYaw) { this->yaw = newYaw; }

	void setPitch(GLfloat newPitch) { this->pitch = newPitch; }


	// ================================================================
	// Functions ======================================================
	// ================================================================

	void move(const float& dt, const int direction)
	{
		//Update position vector
		switch (direction)
		{
		case FORWARD:
			this->position += this->front * this->movementSpeed * dt;
			break;
		case BACKWARD:
			this->position -= this->front * this->movementSpeed * dt;
			break;
		case LEFT:
			this->position -= this->right * this->movementSpeed * dt;
			break;
		case RIGHT:
			this->position += this->right * this->movementSpeed * dt;
			break;
		case UP:
			this->position += this->up * this->movementSpeed * dt;
			break;
		case DOWN:
			this->position -= this->up * this->movementSpeed * dt;
			break;
		case TURN_LEFT:
			this->yaw -= this->sensitivity * dt;
			this->updateCameraVectors();
			break;
		case TURN_RIGHT:
			this->yaw += this->sensitivity * dt;
			this->updateCameraVectors();
			break;
		default:
			break;
		}
	}

	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
	{
		//Update pitch yaw and roll
		this->pitch += static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

		if (this->pitch > 80.f)
			this->pitch = 80.f;
		else if (this->pitch < -80.f)
			this->pitch = -80.f;

		if (this->yaw > 360.f || this->yaw < -360.f)
			this->yaw = 0.f;
	}

	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
	{
		this->updateMouseInput(dt, offsetX, offsetY);
	}

};