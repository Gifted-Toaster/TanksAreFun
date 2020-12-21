#ifndef PRESETMANAGER_H
#define PRESETMANAGER_H

#pragma once

#include "./Constans.h"

#include <string>
#include <map>

class Entity;
class EntityManager;
class Preset;

class PresetManager
{
	// PRESETS
private:
	// Container for the created presets addresses
	std::map<std::string, Preset*> container;
public:	
	// Return the container size
	int presetCount();
	// Create an active entity from a preset
	Entity& LoadPreset(EntityManager* manager, std::string name, int posX, int posY, Direction faceOfDirection);
	// Adding a preset to the container
	Preset& AddPreset(std::string entityName, LayerType layer);

	Preset* GetPresetAt(std::string name);
};

#endif