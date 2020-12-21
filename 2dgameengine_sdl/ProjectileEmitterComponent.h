#pragma once
#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "./glm/glm.hpp"
#include "./EntityManager.h"
#include "./TransformComponent.h"


class ProjectileEmitterComponent : public Component {
private:
	TransformComponent* transform;
	glm::vec2 origin;
	int speed;
	int range;
	float angleRad;
	bool shouldLoop;

public:
	ProjectileEmitterComponent(int speed, int angleDeg, int range,  bool shouldLoop) {
		this->speed = speed;
		this->range = range;
		this->shouldLoop = shouldLoop; // csak loopolja a lovedeket
		/*
		Ne csak megtett tav hanem utkozes es deltaTime feltettellel loopoljon
		Ha elpusztul az ido mulva elindit egy ujabb lovedeket
		*/
		this->angleRad = glm::radians(static_cast<float>(angleDeg));
	}

	ProjectileEmitterComponent(int speed, Direction face, int range, bool shouldLoop) {
		this->speed = speed;
		this->range = range;
		this->shouldLoop = shouldLoop; // csak loopolja a lovedeket
		/*
		Ne csak megtett tav hanem utkozes es deltaTime feltettellel loopoljon
		Ha elpusztul az ido mulva elindit egy ujabb lovedeket
		*/
		switch (face) {
		case LEFT: {
			angleRad = glm::radians(static_cast<float>(180));
			break;
		}
		case RIGHT: {
			angleRad = glm::radians(static_cast<float>(0));
			break;
		}
		case DOWN: {
			angleRad = glm::radians(static_cast<float>(90));
			break;
		}
		case UP: {
			angleRad = glm::radians(static_cast<float>(270));
			break;
		}
		}
	}

	void Initialize() override {
		// When it get initliazied it gets a transform component
		transform = owner->GetComponent<TransformComponent>();
		origin = glm::vec2(transform->position.x, transform->position.y);
		transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
	}

	void Update(float deltaTime) override {
		// Decides in the update loop if it stop exits or refresh
		if (glm::distance(transform->position, origin) > range) {
			if (shouldLoop) {
				transform->position.x = origin.x;
				transform->position.y = origin.y;
			}
			else {
				owner->SetInactive();
			}
		}	
	}

};

#endif // !PROJECTILEEMITTERCOMPONENT_H
