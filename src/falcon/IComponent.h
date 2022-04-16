/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ICOMPONENT_H
#define FALCON_ICOMPONENT_H

#include <string>

namespace falcon {

using ComponentID = int;

class IComponent {
public:
	IComponent(const std::string& name);
	virtual ~IComponent() = 0;

	const std::string getName() const;

	void setId(ComponentID id);
	ComponentID getId() const;

private:
	const std::string _name;
	ComponentID _id;
};

}

#endif // FALCON_ICOMPONENT_H
