/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ENTITY_H
#define FALCON_ENTITY_H

#include <string>
#include <memory>
#include <unordered_map>

#include "Types.h"

namespace falcon {

class IComponent;

class Entity {
public:
	Entity(const std::string& name = "");
	~Entity();

	Entity(Entity&&) = default;
	Entity& operator=(Entity&&) = default;

	EntityID getId() const;
	const std::string getName() const;

	bool addComponent(std::unique_ptr<IComponent>& component);

	IComponent* getComponent(ComponentID id);

private:
	EntityID _id;
	const std::string _name;
	std::unordered_map<ComponentID, std::unique_ptr<IComponent>> _components;
};

}

#endif // FALCON_ENTITY_H
