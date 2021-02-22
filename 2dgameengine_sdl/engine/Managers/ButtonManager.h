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
	
public:
	// Adding the entity to this list if when its get a buttoncomponent
	std::vector<Entity*> container;
	void AddButton(Entity* ent);

	Entity* highlighted_button();
	unsigned int highlighted_index;
	bool IsEmpty();

	// Highlight actions
	void HighLightOnIndex(int index);
	void HighLightNext();
	void HighLightLast();
	ButtonType SelectButton();

};

#endif