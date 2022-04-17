/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_OBJECT_MANAGER_H
#define FALCON_OBJECT_MANAGER_H

#include <vector>
#include <memory>

//#include "Types.h"

namespace falcon {

class IGameObject;

class ObjectManager {
public:
	ObjectManager();
	~ObjectManager();

	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(ObjectManager&) = delete;

//	bool registerObject(IGameObject* object);
//	void unregisterObject(EntityId id);

	

	void clear();

private:
//	void sortByDrawPriority();

private:
//	std::unordered_map<EntityId, IGameObject*> _objects;
};

}

#endif // FALCON_OBJECT_MANAGER_H
