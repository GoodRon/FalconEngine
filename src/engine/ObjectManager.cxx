/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <algorithm>

#include <SDL2/SDL.h>

#include "ObjectManager.h"
#include "WorldObject.h"

using namespace std;

ObjectManager::ObjectManager(Renderer* renderer) :
	m_renderer(renderer),
	m_objects() {
}

ObjectManager::~ObjectManager() {
}

void ObjectManager::pushObject(std::shared_ptr<WorldObject> object) {
	m_objects.push_back(object);
}

void ObjectManager::doObjectsLogic() {
	for (auto & object : m_objects) {
		if (object) {
			object->doLogic();
		}
	}
}

void ObjectManager::drawAllObjects() {
	for (auto & object : m_objects) {
		if (object) {
			object->draw(m_renderer);
		}
	}
}

void ObjectManager::sortByDrawPriority() {
	sort(m_objects.begin(), m_objects.end(), [](
	         const std::shared_ptr<WorldObject>& left,
	const std::shared_ptr<WorldObject>& right) {
		// Если приоритет одинаковый, упорядочивать по координате в мире
		if (left->getDrawPriority() == right->getDrawPriority()) {
			return left->getPositionAndProfile().x < right->getPositionAndProfile().x;
		}

		return left->getDrawPriority() < right->getDrawPriority();
	});
}
