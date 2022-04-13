/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <algorithm>

#include <SDL.h>

#include "ObjectManager.h"
#include "WorldObject.h"
#include "Renderer.h"

namespace falcon {

ObjectManager::ObjectManager(Renderer* renderer) :
	_renderer(renderer),
	_objects() {
}

ObjectManager::~ObjectManager() {
}

void ObjectManager::pushObject(const WorldObjectPointer& object) {
	if (!object) {
		return;
	}

	_objects.push_back(object);
	sortByDrawPriority();
}

void ObjectManager::doObjectsLogic() {
	for (auto &object: _objects) {
		if (object) {
			object->doLogic();
		}
	}
}

void ObjectManager::drawObjects() {
	for (auto &object: _objects) {
		if (object) {
			object->draw(_renderer);
		}
	}
}

WorldObjectPointer ObjectManager::getObjectByCoordinates(int x, int y) {
	WorldObjectPointer result;
	if (!_renderer) {
		return result;
	}

	for (auto &object: _objects) {
		if (!object) {
			continue;
		}

		auto viewport = _renderer->getViewport();
		auto profile = object->getPositionAndProfile();
		if ((x > viewport.x + profile.x) && (x < viewport.x + profile.x + profile.w) &&
			(y > viewport.y + profile.y) && (y < viewport.y + profile.y + profile.h)) {
			result = object;
			break;
		}
	}
	return result;
}

WorldObjectPointer ObjectManager::getObjectById(int id) {
	WorldObjectPointer result;
	// TODO make map
	for (auto &object: _objects) {
		if (object->getId() == id) {
			result = object;
			break;
		}
	}
	return result;
}

void ObjectManager::clear() {
	_objects.clear();
}

void ObjectManager::sortByDrawPriority() {
	std::sort(_objects.begin(), _objects.end(), [](
		const WorldObjectPointer& left, const WorldObjectPointer& right) {

		if (left->getDrawPriority() == right->getDrawPriority()) {
			return left->getPositionAndProfile().x < right->getPositionAndProfile().x;
		}
		return left->getDrawPriority() < right->getDrawPriority();
	});
}

}
