#include "Entity.h"
#include <typeinfo>

Entity::Entity(EntityManager& manager) : manager(manager) {
	this->isActive = true;
}

Entity::Entity(EntityManager& manager, Preset& obj) : manager(manager) , name(obj.getName()) , layer(obj.getLayer())
{
	this->isActive = true;
}

//Entity::Entity(EntityManager& manager ,const Entity &obj) : manager(manager) , name(obj.name) , layer(obj.layer)
//{
//	this->isActive = true;
//	//this->components = new std::vector<Component*>;
//	//this->componentTypeMap = new std::map<std::string, Component*>;
//	for (unsigned int i = 0; i < obj.components.size(); i++) {
//		Component* newComponent = obj.components.at(i);
//		std::cout << i << ". -> Template COMPONENT pointers value: " << obj.components.at(i) << " on address: " << &obj.components.at(i) << " " <<  std::endl;
//		std::cout << "Created COMPONENT pointers value: " << newComponent << " on address: " << &newComponent << " " <<  std::endl;
//		newComponent->owner = this;
//		componentTypeMap[&typeid(*newComponent)] = newComponent;
//		components.emplace_back(newComponent);
//		newComponent->Initialize();
//	}
//	
//}


Entity::Entity(EntityManager& manager , std::string name , LayerType layer) : manager(manager) , name(name) , layer(layer)
{
	this->isActive = true;
}

void Entity::Update(float deltaTime) {
	for (auto& component: components) {
		component->Update(deltaTime);
	}
}

void Entity::Render(){
	for (auto& component : components) {
		component->Render();
	}
}

void Entity::SetInactive()
{
	this->isActive = false;
}

void Entity::Destroy() 
{
	delete this;
}

bool Entity::IsActive() const {
	return this->isActive;
}