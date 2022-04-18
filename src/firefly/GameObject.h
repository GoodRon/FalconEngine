/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_GAME_OBJECT_H
#define FIREFLY_GAME_OBJECT_H

#include <memory>

namespace firefly {

using EntityID = int;

class Entity;
class IEvent;

class GameObject {
public:
	GameObject(const std::shared_ptr<Entity>& entity);
	virtual ~GameObject();

	EntityID getId() const;

	// NOTE do we need this?
	std::shared_ptr<Entity> getEntity() const;

	bool onEvent(const std::shared_ptr<IEvent>& event);

protected:
	virtual bool processEvent(const std::shared_ptr<IEvent>& event);

private:
	std::shared_ptr<Entity> _entity;
};

}

#endif // FIREFLY_GAME_OBJECT_H
