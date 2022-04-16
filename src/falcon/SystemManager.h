/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_SYSTEM_MANAGER_H
#define FALCON_SYSTEM_MANAGER_H

namespace falcon {

using ComponentID = int;

class SystemManager {
public:
	SystemManager();
	~SystemManager();

	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;

	ComponentID registerComponent(const std::unique_ptr<IComponent>& prototype);
	void unregisterComponent(ComponentID id);

	bool findComponent(const std::string& name, ComponentID& id) const;

	

	void clear();

private:
	std::unordered_map<std::string, ComponentID> _names;
	std::unordered_map<ComponentID, std::unique_ptr<IComponent>> _components;
};

}

#endif // FALCON_SYSTEM_MANAGER_H
