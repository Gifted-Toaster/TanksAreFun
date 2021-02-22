#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#pragma once

#include <vector>
#include "./Constans.h"
#include <string>

class Entity;
class EntityManager;

class CollisionManager
{
private:
	EntityManager* manager; 
	// Holders for the collidable objects
	std::vector<Entity*> entities_with_collision;

	
public:
	static bool mouse_button_collision;
	CollisionManager(EntityManager* manager);

	// Main collision logic
	void CheckCollision();
	void MouseCollideWithButton(int posX , int posY);
	void HandleCollision(int i , int j, CollisionType collisionType);
	CollisionType GetCollisionType(std::string name1, std::string name2);

	void RefreshList();

	// Basic list operation methods
	void AddElement(Entity* entity);
	void RemoveElement(int index);
	unsigned int ListSize();
};

#endif