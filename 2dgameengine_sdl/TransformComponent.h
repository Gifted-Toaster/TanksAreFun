#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "./EntityManager.h"
#include "../lib/glm/glm.hpp"
#include <SDL.h>
#include "./Game.h"
#include "./ComponentInit.h"

class TransformComponent : public Component {
public:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 center;
	Direction faceOfDirection; 
	int width;
	int height;
	int scale;

	TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
		position = glm::vec2(posX, posY);
		velocity = glm::vec2(velX, velY);
		width = w;
		height = h;
		faceOfDirection = LEFT;
		center.x = posX + width / 2;
		center.y = posX + height / 2;
		scale = s;
	}

	TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s, Direction face) {
		position = glm::vec2(posX, posY);
		velocity = glm::vec2(velX, velY);
		width = w;
		height = h;
		faceOfDirection = face;
		center.x = posX + width / 2;
		center.y = posX + height / 2;
		scale = s;
	}

	void Update(float deltaTime) override {
		// Step
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;

		center.x = position.x + width / 2;
		center.y = position.y + height / 2;


		// Checking if the entity has left the map
		if (isLeftScene()) {
			// If its a player move him back else destroy
			if (owner->name == "player") {
				position.x -= velocity.x * deltaTime;
				position.y -= velocity.y * deltaTime;
			}
			else {
				owner->SetInactive();
			}
		}
	}

	bool isLeftScene() {
		if (position.x > MAP_WIDTH || position.x < 0) {
			return true;
		}
		if (position.y > MAP_HEIGHT || position.y < 0) {
			return true;
		}
		return false;
	}

	
};

#endif
