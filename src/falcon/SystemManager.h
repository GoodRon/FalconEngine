/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_SYSTEM_MANAGER_H
#define FALCON_SYSTEM_MANAGER_H

#include <string>
#include <unordered_map>
#include <memory>

namespace falcon {

class ISystem;
class IEvent;
class ComponentRegistry;

class SystemManager {
public:
	SystemManager(ComponentRegistry* componentRegistry);
	~SystemManager();

	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;

	template<class T, class... ARGS>
	bool registerSystem(ARGS&&... args) {
		std::shared_ptr<T> sys(new T(std::forward<ARGS>(args)...));

		auto name = sys->getName();
		if (hasSystem(name)) {
			return false;
		}

		if (!sys->resolveComponentIDs(_componentRegistry)) {
			return false;
		}

		_systems[name] = sys;
		return true;
	}

	bool hasSystem(const std::string& name) const;

	// NOTE remove?
	bool onEvent(
		const std::shared_ptr<IEvent>& event) const;

	void clear();

private:
	ComponentRegistry* const _componentRegistry;
	std::unordered_map<std::string, std::unique_ptr<ISystem>> _systems;
};

}

#endif // FALCON_SYSTEM_MANAGER_H
