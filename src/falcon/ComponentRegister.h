/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_MANAGER_H
#define FALCON_COMPONENT_MANAGER_H

#include <string>
#include <memory>
#include <unordered_map>

namespace falcon {

using ComponentID = int;

class ComponentRegister {
public:
	ComponentRegister();
	~ComponentRegister();

	ComponentRegister(const ComponentRegister&) = delete;
	ComponentRegister& operator=(const ComponentRegister&) = delete;

	// TODO template?
	ComponentID addComponent(const std::unique_ptr<IComponent>& prototype);
	void removeComponent(ComponentID id);

	bool findComponentID(const std::string& name, ComponentID& id) const;

	std::shared_ptr<IComponent> getComponent(ComponentID id) const;

	void clear();

private:
	std::unordered_map<std::string, ComponentID> _componentNames;
	std::unordered_map<ComponentID, std::unique_ptr<IComponent>> _componentPrototypes;
};

}

#endif // FALCON_COMPONENT_MANAGER_H
