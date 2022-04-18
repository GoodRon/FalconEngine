/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ISYSTEM_H
#define FIREFLY_ISYSTEM_H

#include <string>
#include <memory>
#include <unordered_map>
#include <forward_list>

#include "Types.h"

namespace firefly {

class IEvent;
class Entity;
class Engine;

class ISystem {
public:
	ISystem(const std::string& name,
		Engine* engine);

	virtual ~ISystem();

	const std::string getName() const;

	bool registerEntity(Entity* entity);
	void unregisterEntity(EntityID id);

	virtual bool onEvent(
		const std::shared_ptr<IEvent>& event) const = 0;

protected:
	bool checkComponents(Entity* entity) const;
	virtual void lockEntities() const;
	virtual void unlockEntities() const;

protected:
	const std::string _name;
	Engine* const _engine;
	std::forward_list<std::string> _requiredComponents;
	std::unordered_map<EntityID, Entity*> _entities;
};

}

#endif // FIREFLY_ISYSTEM_H
