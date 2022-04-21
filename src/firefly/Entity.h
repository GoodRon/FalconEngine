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
	Entity(const std::string& name);
	~Entity() = default;

	Entity(const Entity& other);
	Entity& operator=(const Entity& other);

	Entity(Entity&&) = default;
	Entity& operator=(Entity&&) = default;

	EntityID getId() const;
	const std::string getName() const;

	bool addComponent(const std::string& name, 
		std::unique_ptr<IComponent>&& component);

	IComponent* getComponent(const std::string& name);

	template<class T>
	T* getComponent() {
		const auto id = T::ComponentName;
		if (_components.find(id) == _components.end()) {
			return nullptr;
		}
		return static_cast<T*>(_components[id].get());
	}

private:
	EntityID _id;
	std::string _name;
	std::unordered_map<std::string, 
		std::unique_ptr<IComponent>> _components;
};

}

#endif // FIREFLY_ENTITY_H
