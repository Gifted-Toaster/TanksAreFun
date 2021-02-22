#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "./Game.h";
#include "./Managers/EntityManager.h"
#include "./Entity/Component/TransformComponent.h"
#include "./Entity/Component/ComponentInit.h"

class ColliderComponent : public Component {
public:

	std::string colliderTag;
	SDL_FRect collider;
	SDL_FRect destinationRectangle;
	TransformComponent* transform;
	bool isStatic;

	ColliderComponent(std::string colliderTag, float x, float y, float width, float height) 
	{
		this->colliderTag = colliderTag;
		this->collider = { x , y , width , height }; // new type with these parameters
	}

	ColliderComponent(TileColliderInit init)
	{
		this->colliderTag = "VEGETATION";
		this->collider = { init.x , init.y , init.width , init.height }; // new type with these parameters
	}
	
	void Initialize() override 
	{
		// Checking if the entity had a transform component , otherwise its a tile and has a different collision mechanism
		if (owner->HasComponent<TransformComponent>()) {
			transform = owner->GetComponent<TransformComponent>();
			destinationRectangle = { collider.x ,  collider.y , collider.w , collider.h };
		}
		else { 
			destinationRectangle = { collider.x ,  collider.y , collider.w , collider.h };
			this->isStatic = true;
		}
	}

	void Update(float deltaTime) override 
	{
		if (!isStatic) {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		destinationRectangle.x = collider.x - Game::camera.x;
		destinationRectangle.y = collider.y - Game::camera.y;
	}

	void Render() override {
		SDL_RenderDrawRectF(Game::renderer, &destinationRectangle);
	}

};

#endif