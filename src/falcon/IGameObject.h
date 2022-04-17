/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_IGAME_OBJECT_H
#define FALCON_IGAME_OBJECT_H

#include <memory>

namespace falcon {

using EntityID = int;

class Entity;
class IEvent;

class IGameObject {
public:
	IGameObject(const std::shared_ptr<Entity>& entity);
	virtual ~IGameObject();

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

#endif // FALCON_WORLD_OBJECT_H
