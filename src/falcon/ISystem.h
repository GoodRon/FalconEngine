/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ISYSTEM_H
#define FALCON_ISYSTEM_H

#include <string>
#include <memory>
#include <unordered_map>

#include "Types.h"

namespace falcon {

class IEvent;
class Entity;
class ComponentRegistry;

class ISystem {
public:
	ISystem(const std::string& name);

	virtual ~ISystem();

	const std::string getName() const;

	virtual bool resolveComponentIDs(
		ComponentRegistry* componentRegistry) = 0;

	bool isReady() const;

	bool registerEntity(Entity* entity);
	void unregisterEntity(EntityID id);

	virtual bool onEvent(
		const std::shared_ptr<IEvent>& event) const = 0;

protected:
	virtual bool checkComponents(Entity* entity) const = 0;

protected:
	const std::string _name;
	bool _isReady;
	std::unordered_map<EntityID, Entity*> _entities;
};

}

#endif // FALCON_ISYSTEM_H
