#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#pragma once

#include <vector>
#include "./Constans.h"

class Entity;

class ButtonManager
{
	// BUTTONS
private:
	// A vector which stores the real entities addresses
	std::vector<Entity*> buttons;
public:
	// Adding the entity to this list if when its get a buttoncomponent
	void AddButton(Entity* ent);

	unsigned int highlighted_index;

	// Highlight actions
	void HighLightNext();
	void HighLightLast();
	ButtonType SelectButton();
};

#endif