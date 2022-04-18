/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_OBJECT_MANAGER_H
#define FIREFLY_OBJECT_MANAGER_H

#include <vector>
#include <unordered_map>
#include <memory>

#include "Types.h"

namespace firefly {

class GameObject;
class IEvent;
class SystemManager;

// TODO change to EntityManager
class ObjectManager {
public:
	ObjectManager(SystemManager* systemManager);
	~ObjectManager();

	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(ObjectManager&) = delete;

	bool registerObject(const std::shared_ptr<GameObject>& object);
	void unregisterObject(EntityID id);

	void swapObjects(std::vector<GameObject>& objects);

	bool sendEvent(const std::shared_ptr<IEvent>& event);

	void clear();

private:
	SystemManager* const _systemManager;
	std::unordered_map<EntityID, std::shared_ptr<GameObject>> _objects;
};

}

#endif // FIREFLY_OBJECT_MANAGER_H
