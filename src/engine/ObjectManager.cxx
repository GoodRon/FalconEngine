/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <algorithm>

#include <SDL2/SDL.h>

#include "ObjectManager.h"
#include "WorldObject.h"
#include "Renderer.h"

using namespace std;

ObjectManager::ObjectManager(Renderer* renderer) :
	m_renderer(renderer),
	m_objects() {
}

ObjectManager::~ObjectManager() {
}

void ObjectManager::pushObject(const WorldObjectPointer& object) {
	m_objects.push_back(object);
	sortByDrawPriority();
}

void ObjectManager::doObjectsLogic() {
	for (auto &object : m_objects) {
		if (object) {
			object->doLogic();
		}
	}
}

void ObjectManager::drawAllObjects() {
	for (auto &object : m_objects) {
		if (object) {
			object->draw(m_renderer);
		}
	}
}

WorldObjectPointer ObjectManager::getObjectByCoordinates(int x, int y) {
	WorldObjectPointer result;
	if (!m_renderer) {
		return result;
	}

	for (auto &object: m_objects) {
		if (!object) {
			continue;
		}
		auto viewport = m_renderer->getViewport();
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
	for (auto &object: m_objects) {
		if (object->getId() == id) {
			result = object;
			break;
		}
	}
	return result;
}

void ObjectManager::clear() {
	m_objects.clear();
}

void ObjectManager::sortByDrawPriority() {
	sort(m_objects.begin(), m_objects.end(), [](
		 const WorldObjectPointer& left, const WorldObjectPointer& right) {
		// Если приоритет одинаковый, упорядочивать по координате в мире
		if (left->getDrawPriority() == right->getDrawPriority()) {
			return left->getPositionAndProfile().x < right->getPositionAndProfile().x;
		}

		return left->getDrawPriority() < right->getDrawPriority();
	});
}
