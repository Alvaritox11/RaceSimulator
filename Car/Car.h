#pragma once

#include "libs.h"

class Car {
public:

    Car() : position(glm::vec3(0.0f)), orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
        carModel(nullptr), cam(glm::vec3(0.7f, 1.f, -2.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)) {
    }

    Car(const glm::vec3& initialPosition, Model* model, Camera camera)
        : position(initialPosition), orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), carModel(model), cam(camera) {
    }

    // Getters
    glm::vec3 getPosition() const { return position; }
    glm::quat getOrientation() const { return orientation; }
    Camera getCamera() const { return cam; }

    // Setters
    void setPosition(const glm::vec3& newPosition) { position = newPosition; }
    void setOrientation(const glm::quat& newOrientation) { orientation = newOrientation; }
    void setCamera(const Camera& newCamera) { cam = newCamera; }

    void updateOrientation(float angle, const glm::vec3& axis) {
        glm::quat rotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
        orientation = glm::normalize(rotation * orientation);
    }

    // Funci�n para mover el coche hacia adelante en su direcci�n actual
    void moveForward(float speed) {
        glm::vec3 forwardVector = orientation * glm::vec3(0.0f, 0.0f, -1.0f);
        position += speed * glm::normalize(forwardVector);
    }

    // Funci�n para obtener la matriz de modelo-vista del coche
    glm::mat4 getModelViewMatrix() const {
        return glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(orientation);
    }

    // Otras funciones y propiedades del coche seg�n sea necesario

private:
    glm::vec3 position;        // Posici�n del coche
    glm::quat orientation;     // Cuaterni�n para representar la orientaci�n del coche


    Model* carModel;		// Modelo del coche
    Camera cam;				// C�mara del coche
    // Otras propiedades del coche
};


