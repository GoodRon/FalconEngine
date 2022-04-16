/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_IENTITY_H
#define FALCON_IENTITY_H

namespace falcon {

using EntityID = int;
using ComponentID = int;

class IEntity {
public:
	IEntity();
	virtual ~IEntity() = 0;

	EntityID getId() const;

	void addComponent(const std::shared_ptr<IComponent>& component);
	removeComponent(ComponentID id);

	std::shared_ptr<IComponent> getComponent(ComponentID id) const;

private:
	EntityID _id;
	std::unordered_map<ComponentID, std::unique_ptr<IComponent>> _components;
};

}

#endif // FALCON_IENTITY_H
