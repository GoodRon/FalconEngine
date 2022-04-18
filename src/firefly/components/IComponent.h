/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ICOMPONENT_H
#define FIREFLY_ICOMPONENT_H

#include <string>
#include <memory>

#include "Types.h"

namespace firefly {

ComponentID getComponentId(const std::string& name);

class IComponent {
public:
	IComponent(const std::string& name);
	virtual ~IComponent() = 0;

	const std::string getName() const;
	ComponentID getId() const;

private:
	const std::string _name;
	const ComponentID _id;
};

}

#endif // FIREFLY_ICOMPONENT_H
