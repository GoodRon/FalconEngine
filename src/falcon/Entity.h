/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ENTITY_H
#define FALCON_ENTITY_H

#include <memory>
#include <unordered_map>

#include "Types.h"

namespace falcon {

class IComponent;

class Entity {
public:
	Entity();
	~Entity();

	Entity(Entity&&) = default;
	Entity& operator=(Entity&&) = default;

	EntityID getId() const;

	bool addComponent(std::unique_ptr<IComponent>& component);

	IComponent* getComponent(ComponentID id);

private:
	EntityID _id;
	std::unordered_map<ComponentID, std::unique_ptr<IComponent>> _components;
};

}

#endif // FALCON_ENTITY_H
