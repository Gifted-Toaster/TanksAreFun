#pragma once
#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H
	
#include "./glm/glm.hpp"
#include "./Managers/EntityManager.h"
#include "./Entity/Component/TransformComponent.h"


// Nincs semmi ami lovedek e komponenset kozvetlenul a kilovo entity-hez kotne igy nemtudja frissiteni az originjet a konstrukcio utan
class ProjectileEmitterComponent : public Component {
private:
	// This one hold the owner entities transform component
	TransformComponent* transform;

	// And these ones are the direct link to the entity which created the owner of this entity
	TransformComponent* owner_transform;
	Entity* projectile_owner;


	glm::vec2 origin;
	int speed;
	int range;
	float angleRad;
	bool shouldLoop;
	void setFace(Direction face) {
		switch (face) {
		case LEFT: {
			this->angleRad = glm::radians(static_cast<float>(180));
			break;
		}
		case RIGHT: {
			this->angleRad = glm::radians(static_cast<float>(0));
			break;
		}
		case DOWN: {
			this->angleRad = glm::radians(static_cast<float>(90));
			break;
		}
		case UP: {
			this->angleRad = glm::radians(static_cast<float>(270));
			break;
		}
		}
	}
public:
	
	ProjectileEmitterComponent(int speed, int angleDeg, int range,  bool shouldLoop, Entity* real_owner) {
		projectile_owner = real_owner;
		this->speed = speed;
		this->range = range;
		this->shouldLoop = shouldLoop; // csak loopolja a lovedeket
		this->angleRad = glm::radians(static_cast<float>(angleDeg));
	}

	ProjectileEmitterComponent(int speed, Direction face, int range, bool shouldLoop, Entity* real_owner) {
		projectile_owner = real_owner;
		this->speed = speed;
		this->range = range;
		this->shouldLoop = shouldLoop; // csak loopolja a lovedeket
		setFace(face);
	}

	void Initialize() override {
		// When it get initliazied it gets a transform component
		transform = owner->GetComponent<TransformComponent>();

		if (projectile_owner) { // If it has a real owner then sets the current base point
			owner_transform = projectile_owner->GetComponent<TransformComponent>();
		}

		origin = glm::vec2(transform->position.x, transform->position.y);
		transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
	}

	void Update(float deltaTime) override {
		// Decides in the update loop if it stop exits or refresh
		if (glm::distance(transform->position, origin) > range) {
 			if (this->shouldLoop) { 
				// If the projectile traveled the range distance from its starting point then and it should loop then restart on the new base point				
				transform->position = owner_transform->center;
				origin = owner_transform->center;

				// We have to refresh the direction aswell
				setFace(projectile_owner->GetComponent<TransformComponent>()->faceOfDirection);
				transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed); // This one needed after dir change
			}
			else {
				owner->SetInactive();
			}
		}	
	}

};

#endif // !PROJECTILEEMITTERCOMPONENT_H
