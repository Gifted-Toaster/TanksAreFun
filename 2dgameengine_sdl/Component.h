#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>

class Entity;

class Component {
public:
	Entity* owner;
	virtual ~Component() {}
	virtual void Initialize() {}
	virtual void Update(float deltaTime) {}
	virtual void Render() {}
	Component() { owner = NULL; };
};

#endif // !COMPONENT_H

