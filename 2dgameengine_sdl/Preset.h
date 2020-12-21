#ifndef PRESET_H
#define PRESET_H

#pragma once

#include <map>
#include <string>
#include <vector>
#include "./Constans.h"

class Preset {
private:
	std::string name;
	LayerType layer;
	
public:
	std::map<ComponentType, std::vector<std::string>> components;

	Preset(std::string EntityName , LayerType layer) {
		name = EntityName;
		this->layer = layer;
	}
	Preset() { name = "";};

	void AddComponent(ComponentType compType , std::string compData) {
		components[compType].push_back(compData);
	}
	
	std::string getName() {
		return name;
	}
	LayerType getLayer() {
		return layer;
	}

};

#endif
