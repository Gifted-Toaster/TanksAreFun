#include "CollisionManager.h"
#include "./Collision.h"
#include "./ColliderComponent.h"
#include "./Component.h"
#include "./Entity.h"
#include "./Game.h"

#include <string>

void CollisionManager::CheckCollision()
{
	RefreshList();

	// 1) Itterate through our active entities with collider component
	// 2) create collider pairs
	// 3) decide what happens with them

	// Safe check for empti collision array
	if (entities_with_collision.size() > 0) 
	{
		// 1)
   		for (int i = 0; i < entities_with_collision.size() - 1; i++)
		{
			for (int j = i + 1; j < entities_with_collision.size(); j++)
			{
				// 2)
				if (Collision::CheckRectangleCollision(
					entities_with_collision.at(i)->GetComponent<ColliderComponent>()->collider,
					entities_with_collision.at(j)->GetComponent<ColliderComponent>()->collider)
					)
				{
					// 3)
					HandleCollision(
						i,
						j,
						GetCollisionType(
							entities_with_collision.at(i)->GetComponent<ColliderComponent>()->colliderTag,
							entities_with_collision.at(j)->GetComponent<ColliderComponent>()->colliderTag
						)
					);
				}
			}
		}
	}
	else {
		return;
	}

}

void CollisionManager::HandleCollision(int i, int j, CollisionType collisionType)
{

    switch (collisionType) {
        case PLAYER_ENEMY_COLLISION:
            //Game::DamagePlayer(entities_with_collision.at(j));
            std::cout << "PLAYER_ENEMY_COLLISION\n";
            break;
        case PLAYER_PROJECTILE_COLLISION:
            // lose health
			//Game::DamagePlayer(entities_with_collision.at(j));
            std::cout << "PLAYER_PROJECTILE_COLLISION\n";
            break;
        case PLAYER_LEVEL_COMPLETE_COLLISION:
            // TODO atvezeto oldal
            std::cout << "PLAYER_LEVEL_COMPLETE_COLLISION\n";
			Game::ProcessNextLevel();
            break;
        case PLAYER_VEGETATION_COLLISION:
			std::cout << "TERRAIN BLOCK";
            break;
        case ENEMY_PROJECTILE_COLLISION:
            // Enemy lose health
            std::cout << "ENEMY_PROJECTILE_COLLISION\n";
			entities_with_collision.at(i)->SetInactive();
            // projectile destory
			entities_with_collision.at(j)->SetInactive();
            break;
        case NO_COLLISION:
            break;
    }

}

CollisionType CollisionManager::GetCollisionType(std::string name1, std::string name2)
{
	if (!name1.compare("PLAYER") || !name2.compare("PLAYER")) {
		if (!name1.compare("ENEMY") || !name2.compare("ENEMY")) {
			return PLAYER_ENEMY_COLLISION;
		}
		if (!name1.compare("PROJECTILE") || !name2.compare("PROJECTILE")) {
			return PLAYER_PROJECTILE_COLLISION;
		}
		if (!name1.compare("LEVEL_COMPLETE") || !name2.compare("LEVEL_COMPLETE")) {
			return PLAYER_LEVEL_COMPLETE_COLLISION;
		}
		if (!name1.compare("VEGETATION") || !name2.compare("VEGETATION")) {
			return PLAYER_VEGETATION_COLLISION;
		}
	}


	if (!name1.compare("ENEMY") || !name2.compare("ENEMY")) {
		if (!name1.compare("PROJECTILE") || !name2.compare("PROJECTILE")) {
			return ENEMY_PROJECTILE_COLLISION;
		}
		if (!name1.compare("FRIENDLY_PROJECTILE") || !name2.compare("FRIENDLY_PROJECTILE")) {
			return ENEMY_PROJECTILE_COLLISION;

		}
	}
}

void CollisionManager::RefreshList()
{
	for (int i = 0; i < entities_with_collision.size();i++) {
		if (!entities_with_collision.at(i)->IsActive()) {
			RemoveElement(i);
			i--;
		}
	}
}

void CollisionManager::AddElement(Entity* entity)
{
	entities_with_collision.emplace_back(entity);
}

void CollisionManager::RemoveElement(int index)
{
	entities_with_collision.erase(entities_with_collision.begin()+index);
}

unsigned int CollisionManager::ListSize()
{
	return entities_with_collision.size();
}
