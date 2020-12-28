#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#pragma once

#include <vector>
#include <map>

#include "./Entity.h"
#include "./Component.h"
#include "./ButtonManager.h"
#include "./PresetManager.h"
#include "./CollisionManager.h"


class EntityManager
{
	// ENTITIES
private:
	// Container for all entities
	std::vector<Entity*> entities[NUM_LAYERS];

	//std::vector<std::vector<Entity*>> entities;
	std::vector<Entity*> inactive_entites;

public:
	// Manager for buttons
	ButtonManager buttons;
	// Manager for presets
	PresetManager presets;
	// Manager for collision
	CollisionManager collision;


	// Main loop methods
	void Update(float deltaTime);
	void Render();

	// Getters
	unsigned int GetColliderSize();
	unsigned int GetInactiveCount() const;
	//std::vector<Entity*> GetEntitites() const;
	std::vector<Entity*> GetEntititesByLayer(LayerType layer) const;
	Entity* GetEntityByName(std::string entityName) const;
	unsigned int GetEntityCount() const;
	Entity* GetPlayer() const;
	void ListAllEntites() const;

	// Setters
	Entity& AddEntity(std::string entityName, LayerType layer);
	void AddEntity(Entity* preset);

	// Operation methods
	void ClearData();
	bool HasNoEntities() const;
	void DestroyInactiveEntities();

	Entity* GetInactiveByName(std::string name);
 	
};
#endif
