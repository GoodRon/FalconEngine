/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "ObjectManager.h"

#include "IGameObject.h"

namespace falcon {

ObjectManager::ObjectManager():
    _objects() {
}

ObjectManager::~ObjectManager() {
}

bool ObjectManager::registerObject(
    const std::shared_ptr<IGameObject>& object) {
    if (!object) {
        return false;
    }

    const auto id = object->getId();
    if (_objects.find(id) != _objects.end()) {
        return true;
    }

    _objects[id] = object;
    return true;
}

void ObjectManager::unregisterObject(EntityID id) {
    _objects.erase(id);
}

void ObjectManager::swapObjects(
    std::vector<IGameObject>& objects) {

}

bool ObjectManager::sendEvent(
    const std::shared_ptr<IEvent>& event) {
    // TODO write me

    for (auto& object: _objects) {
        if (object.second->onEvent(event)) {
            break;
        }
    }
    return true;
}

void ObjectManager::clear() {
	_objects.clear();
}

}
