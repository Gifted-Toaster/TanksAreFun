#include "PresetManager.h"
#include "./ColliderComponent.h"
#include "./SpriteComponent.h"
#include "./TextLabelComponent.h"
#include "./ProjectileEmitterComponent.h"
#include "./KeyboardControlComponent.h"
#include "./ButtonComponent.h"
#include "./Entity.h"
#include "./Preset.h"

#include <string>

Preset& PresetManager::AddPreset(std::string entityName, LayerType layer) {
	Preset* preset = new Preset(entityName, layer);
	container.emplace(entityName, preset);
	return *preset;
}

Preset* PresetManager::GetPresetAt(std::string name)
{
	return container[name];
}

int PresetManager::presetCount()
{
	return container.size();
}

// Instead of passing the position upon creation we pass the address of the entity which called the preset
// for creating a direct link between the two object
Entity& PresetManager::LoadPreset(EntityManager *manager, std::string name, Entity* real_owner, Direction faceOfDirection) {

	// Creates a new entity based on the preset
	Entity* entity = new Entity(*manager, *container[name]);

	// Creates an iterrator for map type ( our container )
	std::map<ComponentType, std::vector<std::string>>::iterator it = container[name]->components.begin();

	// Itterates through our container
	for (std::pair<ComponentType, std::vector<std::string>> element : container[name]->components) {
		/* 
		Accessing KEY from element
		And decide which time of compononent should it add
		Then creates a component and add to the template entity above
		*/
		switch (element.first) {
		case TRANSFORM: {
			float X = real_owner->GetComponent<TransformComponent>()->center.x;
			float Y = real_owner->GetComponent<TransformComponent>()->center.y;
			float velX = std::stoi(element.second.at(2));
			float velY = std::stoi(element.second.at(3));
			float width = std::stoi(element.second.at(4));
			float height = std::stoi(element.second.at(5));
			float scale = std::stoi(element.second.at(6));
			entity->AddComponent<TransformComponent>(X, Y, velX, velY, width, height, scale);
			break;
		}
		case TILE: {
			break;
		}
		case TEXTLABEL: {

			int x = std::stoi(element.second.at(0));
			int y = std::stoi(element.second.at(1));
			std::string text = element.second.at(2);
			std::string fontFamily = element.second.at(3);
			//SDL_Color color = element.second.at(4); // Erre majd talalj ki valamit
			bool dinamic = element.second.at(4).compare("true") ? true : false;
			entity->AddComponent<TextLabelComponent>(x, y, text, fontFamily, GREEN_COLOR, dinamic);
			break;
		}
		case SPRITE: {
			std::string textureId = element.second.at(0);
			if (element.second.size() == 1) {
				entity->AddComponent<SpriteComponent>(textureId);
			}
			else {
				std::string textureId = element.second.at(0);
				int numFrames = std::stoi(element.second.at(1));
				int animationSpeed = std::stoi(element.second.at(2));
				bool hasDirections = element.second.at(3).compare("true") ? true : false;
				bool isFixed = element.second.at(4).compare("true") ? true : false;
				entity->AddComponent<SpriteComponent>(textureId, numFrames, animationSpeed, hasDirections, isFixed);
			}
			break;
		}
		case KEYBOARD:
			//entity->AddComponent<KeyboardControlComponent>();
			break;
		case COLLIDER:
		{
			std::string colliderTag = element.second.at(0);
			float x = std::stoi(element.second.at(1));
			float y = std::stoi(element.second.at(2));
			float width = std::stoi(element.second.at(3));
			float height = std::stoi(element.second.at(4));
			entity->AddComponent<ColliderComponent>(colliderTag, x, y, width, height);
			break;
		}
		case PROJECTILE_EMITTER:
		{
			int speed = std::stoi(element.second.at(0));
			int range = std::stoi(element.second.at(2));
			bool loop = element.second.at(3).compare("1") ? false : true;
			entity->AddComponent<ProjectileEmitterComponent>(speed, faceOfDirection, range, loop , real_owner);
			break;
		}
		default:
			std::cout << "Component type did not found." << std::endl;
			break;
		}
	}
	// Add the template to our main managers container , then returns it
	manager->AddEntity(entity);
	return *entity;
}