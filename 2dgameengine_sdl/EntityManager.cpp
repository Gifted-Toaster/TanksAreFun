#include "./EntityManager.h"
#include "./Collision.h"
#include "./ColliderComponent.h"

#include <iostream>

// PROPER VECTOR CLEAR
void EntityManager::DeleteData() // Free the memory on the heap
{
	for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
		if (entities[layerNumber].size() != 0) {
			for (auto& entity : entities[layerNumber]) {
				delete entity;
			}
			entities[layerNumber].clear();
		}
	}
}

// DONT USE THIS
// Iterate through each layer , if there is an element in that layer then free its entities from memory than clear the vector
void EntityManager::ClearData() 
{
	for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
		if (entities[layerNumber].size() != 0) {
			for (auto& entity : entities[layerNumber]) {
				entity->Destroy();
			}
			entities[layerNumber].clear();
		}
	}
}

bool EntityManager::HasNoEntities() const {
	return GetEntityCount() == 0;
}

unsigned int EntityManager::GetColliderSize()
{
	return collision.ListSize();
}

unsigned int EntityManager::GetInactiveCount() const
{
	return inactive_entites.size();
}

// Update every entitiy
void EntityManager::Update(float deltaTime) {
	for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
		for (int j = 0; j < entities[layerNumber].size() ; j++) {
			entities[layerNumber].at(j)->Update(deltaTime);
			// After this update cycle if the currently entity becomes inactive then we replace it in another array to reduce update time
			if (!entities[layerNumber].at(j)->IsActive()) 
			{
 				inactive_entites.push_back(entities[layerNumber].at(j));
				std::cout << "Object removed from: " << entities[layerNumber].at(j) << std::endl;

				entities[layerNumber].erase(entities[layerNumber].begin() + j);

				std::cout << "Object replaced to inactives at: " << inactive_entites.at(inactive_entites.size()-1) << std::endl;
				//entities.erase(entities.begin() + i);
				j--;
			}
		}
	}
	
}

void EntityManager::Render() {

	for (int layerNumber = 0; layerNumber < NUM_LAYERS ; layerNumber++) {
		for (auto& entity : entities[layerNumber]) {
			entity->Render();
		}
	}
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
	// Decide what kind of entities are we loading
	Entity* entity = new Entity(*this, entityName, layer);
	// If the element is collidable
	if (entity->HasComponent<ColliderComponent>())
	{
		collision.AddElement(entity);
	}
	// Places the instance on the corresponding entry
	entities[static_cast<int>(layer)].emplace_back(entity);
	std::cout << entity << " ...\n";
	return *entity;
}

void EntityManager::AddEntity(Entity* preset)
{
	// Same for presets
		// If the element is collidable
	std::cout << "Created from preset at: " << preset << std::endl;
	if (preset->HasComponent<ColliderComponent>())
	{
		collision.AddElement(preset);
	}
	entities[static_cast<int>(preset->layer)].emplace_back(preset);

	std::cout << "Placed in entity list at: " << entities[static_cast<int>(preset->layer)].at(entities[static_cast<int>(preset->layer)].size() - 1) << std::endl;
}


//std::vector < std::vector<Entity*> > EntityManager::GetEntitites() const {
//	return entities;
//}

unsigned int EntityManager::GetEntityCount() const {
	int size = 0;
	for (int i = 0; i < NUM_LAYERS; i++) {
		size += entities[i].size();
	}
	return size;
}

Entity* EntityManager::GetPlayer() const {
	for (auto* entity : entities[PLAYER_LAYER]) {
		if (entity->name.compare("player") == 0) {
			return entity;
		}
	}
	return NULL;
}


Entity* EntityManager::GetEntityByName(std::string entityName) const {

	for (int i = 0; i < NUM_LAYERS; i++) {
		for (auto* entity : entities[i]) {
			if (entity->name.compare(entityName) == 0) {
				return entity;
			}
		}
	}
	return NULL;
	
}

void EntityManager::DestroyInactiveEntities()
{
	for (auto& entitites : inactive_entites) {
		delete entitites;
	}
	inactive_entites.clear();
}

Entity* EntityManager::GetInactiveByName(std::string name)
{
	for (int i = 0; i < inactive_entites.size(); i++) {
		if (inactive_entites.at(i)->name.compare(name)) {
			return inactive_entites.at(i);
		}
	}
	return NULL;
}
