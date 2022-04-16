/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_SYSTEM_MANAGER_H
#define FALCON_SYSTEM_MANAGER_H

#include <unordered_map>
#include <memory>

namespace falcon {

using ComponentID = int;

class IComponent;

class SystemManager {
public:
	SystemManager();
	~SystemManager();

	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;

	

	void clear();

private:
//	std::unordered_map<std::string, ComponentID> _names;
//	std::unordered_map<ComponentID, std::unique_ptr<IComponent>> _components;
};

}

#endif // FALCON_SYSTEM_MANAGER_H
