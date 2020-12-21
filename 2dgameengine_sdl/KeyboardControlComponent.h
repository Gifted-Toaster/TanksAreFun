#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include "./EntityManager.h"
#include "./TransformComponent.h"

class KeyboardControlComponent : public Component {
public:
	// Keys we wanna use in game
	std::string upKey;
	std::string downKey;
	std::string rightKey;
	std::string leftKey;
	std::string actionKey;
	TransformComponent* transform;
	SpriteComponent* sprite;

	// Key definitions
	KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey , std::string shootKey) {
		this->upKey = GetSDLKeyStringCode(upKey);
		this->rightKey = GetSDLKeyStringCode(rightKey);
		this->downKey = GetSDLKeyStringCode(downKey);
		this->leftKey = GetSDLKeyStringCode(leftKey);
		this->actionKey = GetSDLKeyStringCode(shootKey);
	}
	std::string GetSDLKeyStringCode(std::string key) {
		if (key.compare("up") == 0) return "1073741906";
		if (key.compare("down") == 0) return "1073741905";
		if (key.compare("left") == 0) return "1073741904";
		if (key.compare("right") == 0) return "1073741903";
		if (key.compare("space") == 0) return "32";
		
		return std::to_string(static_cast<int>(key[0]));
	}

	void Initialize() override {
		transform = owner->GetComponent<TransformComponent>();
		sprite = owner->GetComponent<SpriteComponent>();
	}

	void Update(float deltaTime) override {
		// Checking for SDL_events 
		// It's in the game.cpp
		// If happens then decides which action is going to be called based on the comparison of the definitions above
		if (!owner->name.compare("player")) {
			if (Game::event.type == SDL_KEYDOWN) {
				std::string keyCode = std::to_string(Game::event.key.keysym.sym);
				// Can't be a switch statement since it need int or enum
				if (keyCode.compare(upKey) == 0) {
					transform->velocity.y = -50;
					transform->velocity.x = 0;
					transform->faceOfDirection = UP;
					sprite->Play("UpAnimation");
				}
				if (keyCode.compare(rightKey) == 0) {
					transform->velocity.y = 0;
					transform->velocity.x = 50;
					transform->faceOfDirection = RIGHT;
					sprite->Play("RightAnimation");
				}
				if (keyCode.compare(leftKey) == 0) {
					transform->velocity.y = 0;
					transform->velocity.x = -50;
					transform->faceOfDirection = LEFT;
					sprite->Play("LeftAnimation");
				}
				if (keyCode.compare(downKey) == 0) {
					transform->velocity.y = 50;
					transform->velocity.x = 0;
					transform->faceOfDirection = DOWN;
					sprite->Play("DownAnimation");
				}
				if (keyCode.compare(actionKey) == 0) {
					Game::spawnEntity("projectile", transform->center.x, transform->center.y, transform->faceOfDirection);
				}
			}
			if (Game::event.type == SDL_KEYUP) {
				std::string keyCode = std::to_string(Game::event.key.keysym.sym);

				if (keyCode.compare(upKey) == 0) {
					transform->velocity.y = 0;
				}
				if (keyCode.compare(rightKey) == 0) {
					transform->velocity.x = 0;
				}
				if (keyCode.compare(leftKey) == 0) {
					transform->velocity.x = 0;
				}
				if (keyCode.compare(downKey) == 0) {
					transform->velocity.y = 0;
				}
				if (keyCode.compare(actionKey) == 0) {
					//...
				}
			}
		}

		if (!owner->name.compare("controller")) {
			if (Game::event.type == SDL_KEYDOWN) {
				std::string keyCode = std::to_string(Game::event.key.keysym.sym);
				// Can't be a switch statement since it need int or enum
				
				if (keyCode.compare(upKey) == 0) {
					// move up with the highlight
					Game::StepUp();
				}
				if (keyCode.compare(downKey) == 0) {
					// move down with the highlight
					Game::StepDown();
				}
				if (keyCode.compare(actionKey) == 0) {
					// select current button
					Game::Select();
				}
			}
		}
		
	}
};
#endif // !KEYBOARDCONTROLCOMPONENT_H

