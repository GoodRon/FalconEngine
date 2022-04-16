/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_IENTITY_H
#define FALCON_IENTITY_H

#include <memory>
#include <unordered_map>

namespace falcon {

using EntityID = int;
using ComponentID = int;

class IComponent;

class IEntity {
public:
	IEntity();
	virtual ~IEntity() = 0;

	void setId(EntityID id);
	EntityID getId() const;

	bool addComponent(const std::shared_ptr<IComponent>& component);
	void removeComponent(ComponentID id);

	std::shared_ptr<IComponent> getComponent(ComponentID id);

private:
	EntityID _id;
	std::unordered_map<ComponentID, std::shared_ptr<IComponent>> _components;
};

}

#endif // FALCON_IENTITY_H
