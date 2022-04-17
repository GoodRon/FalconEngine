/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "ObjectManager.h"

#include "Entity.h"
#include "SystemManager.h"
#include "GameObject.h"

namespace falcon {

ObjectManager::ObjectManager(SystemManager* systemManager):
    _systemManager(systemManager),
    _objects() {
}

ObjectManager::~ObjectManager() {
}

bool ObjectManager::registerObject(
    const std::shared_ptr<GameObject>& object) {
    if (!object) {
        return false;
    }

    const auto id = object->getId();
    if (_objects.find(id) != _objects.end()) {
        return true;
    }

    _objects[id] = object;

    _systemManager->registerEntity(object->getEntity().get());
    return true;
}

void ObjectManager::unregisterObject(EntityID id) {
    auto it = _objects.find(id);
    if (it == _objects.end()) {
        return;
    }

    _systemManager->unregisterEntity((*it).second->getEntity()->getId());
    _objects.erase(id);
}

void ObjectManager::swapObjects(
    std::vector<GameObject>& objects) {


    // TODO write me!
    // register/unregister
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
