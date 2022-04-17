/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
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

	void push(const WorldObjectPointer& object);

	void updateAll();

	void drawAll();

	WorldObjectPointer getByCordinates(int x, int y);

	WorldObjectPointer getById(int id);

	void clear();

private:
	void sortByDrawPriority();

private:
	Renderer* _renderer;
	std::vector<WorldObjectPointer> _objects;
};

}

#endif // FALCON_OBJECT_MANAGER_H
