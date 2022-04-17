/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_OBJECT_MANAGER_H
#define FALCON_OBJECT_MANAGER_H

#include <vector>
#include <unordered_map>
#include <memory>

#include "Types.h"

namespace falcon {

class IGameObject;
class IEvent;

class ObjectManager {
public:
	ObjectManager();
	~ObjectManager();

	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(ObjectManager&) = delete;

	bool registerObject(IGameObject* object);
	void unregisterObject(EntityID id);

	void swapObjects(std::vector<IGameObject>& objects);

	bool sendEvent(const std::shared_ptr<IEvent>& event);

	void clear();

private:
	std::unordered_map<EntityID, IGameObject*> _objects;
};

}

#endif // FALCON_OBJECT_MANAGER_H
