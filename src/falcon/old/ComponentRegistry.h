/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_MANAGER_H
#define FALCON_COMPONENT_MANAGER_H

#include <string>
#include <memory>
#include <unordered_map>

#include "Types.h"

namespace falcon {

class IComponent;

class ComponentRegistry {
public:
	ComponentRegistry();
	~ComponentRegistry();

	ComponentRegistry(const ComponentRegistry&) = delete;
	ComponentRegistry& operator=(const ComponentRegistry&) = delete;

	template<class T, class... ARGS>
	ComponentID registerComponent(ARGS&&... args) {
		std::unique_ptr<T> component(new T(std::forward<ARGS>(args)...));

		auto name = component->getName();
		falcon::EntityID id = findComponentID(name);

		if (id >= 0) {
			return id;
		}

		id = getNextId();

		component->setId(id);
		_componentIds[name] = id;
		_prototypes[id] = std::move(component);
		return id;
	}

	void unregisterComponent(ComponentID id);

	ComponentID findComponentID(const std::string& name);

	std::unique_ptr<IComponent> makeComponent(ComponentID id);

	void clear();

private:
	ComponentID getNextId();

private:
	int _nextId;
	std::unordered_map<std::string, ComponentID> _componentIds;
	std::unordered_map<ComponentID, std::unique_ptr<IComponent>> _prototypes;
};

}

#endif // FALCON_COMPONENT_MANAGER_H
