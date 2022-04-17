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

	bool addComponent(std::unique_ptr<IComponent>& component);

	IComponent* getComponent(ComponentID id);

private:
	EntityID _id;
	std::unordered_map<ComponentID, std::unique_ptr<IComponent>> _components;
};

}

#endif // FALCON_IENTITY_H
