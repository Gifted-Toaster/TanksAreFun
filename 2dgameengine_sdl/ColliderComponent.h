#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "./Game.h";
#include "./EntityManager.h"
#include "./TransformComponent.h"
#include "./ComponentInit.h"

class ColliderComponent : public Component {
public:

	std::string colliderTag;
	SDL_Rect collider;
	SDL_Rect destinationRectangle;
	TransformComponent* transform;
	bool isStatic;

	ColliderComponent(std::string colliderTag, int x, int y, int width, int height) 
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
		// Checking if the entity had a transform component , otherwise the whole collision is not working
		// We have to expand this for tiles which have no transform component
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
		SDL_RenderDrawRect(Game::renderer, &destinationRectangle);
	}

};

#endif