#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#pragma once

#include <vector>
#include "./Constans.h"
#include <string>

class Entity;

class CollisionManager
{
private:
	// Holders for the collidable objects
	std::vector<Entity*> entities_with_collision;
public:
	// Main collision logic
	void CheckCollision();
	void HandleCollision(int i , int j, CollisionType collisionType);
	CollisionType GetCollisionType(std::string name1, std::string name2);

	void RefreshList();

	// Basic list operation methods
	void AddElement(Entity* entity);
	void RemoveElement(int index);
	unsigned int ListSize();
};

#endif