/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_OBJECT_MANAGER_H
#define FALCON_OBJECT_MANAGER_H

#include <vector>
#include <memory>

namespace falcon {

class WorldObject;
class Renderer;

using WorldObjectPointer = std::shared_ptr<WorldObject>;

class ObjectManager {
public:
	ObjectManager(Renderer* renderer);

	~ObjectManager();

	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(ObjectManager&) = delete;

	void pushObject(const WorldObjectPointer& object);

	void doObjectsLogic();

	void drawObjects();

	WorldObjectPointer getObjectByCoordinates(int x, int y);

	WorldObjectPointer getObjectById(int id);

	void clear();

private:
	void sortByDrawPriority();

private:
	Renderer* _renderer;
	std::vector<WorldObjectPointer> _objects;
};

}

#endif // FALCON_OBJECT_MANAGER_H
