/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ISYSTEM_H
#define FALCON_ISYSTEM_H

#include <string>
#include <memory>
#include <unordered_set>

namespace falcon {

class IEvent;
class IEntity;
class ComponentRegistry;

class ISystem {
public:
	ISystem(const std::string& name);

	virtual ~ISystem();

	const std::string getName() const;

	virtual bool resolveComponentIDs(
		ComponentRegistry* componentRegistry) = 0;

	bool isReady() const;

	bool registerEntity(IEntity* entity);
	void unregisterEntity(IEntity* entity);

	virtual bool onEvent(
		const std::shared_ptr<IEvent>& event) const = 0;

protected:
	virtual bool checkComponents(IEntity* entity) const = 0;

	void setReady(bool isReady);

private:
	const std::string _name;
	bool _isReady;
	std::unordered_set<IEntity*> _entities;
};

}

#endif // FALCON_ISYSTEM_H
