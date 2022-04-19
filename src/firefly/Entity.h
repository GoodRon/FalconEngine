/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ENTITY_H
#define FIREFLY_ENTITY_H

#include <string>
#include <memory>
#include <unordered_map>

#include "Types.h"

namespace firefly {

class IComponent;

class Entity {
public:
	Entity(const std::string& name = "");
	~Entity() = default;

	Entity(const Entity& other);
	Entity& operator=(const Entity& other);

	Entity(Entity&&) = default;
	Entity& operator=(Entity&&) = default;

	EntityID getId() const;
	const std::string getName() const;

	bool addComponent(std::unique_ptr<IComponent>&& component);

	IComponent* getComponent(ComponentID id);

private:
	EntityID _id;
	std::string _name;
	std::unordered_map<ComponentID, std::unique_ptr<IComponent>> _components;
};

}

#endif // FIREFLY_ENTITY_H
