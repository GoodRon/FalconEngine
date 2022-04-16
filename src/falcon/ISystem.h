/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ISYSTEM_H
#define FALCON_ISYSTEM_H

#include <string>

namespace falcon {

using ComponentID = int;

class ISystem {
public:
	ISystem(const std::string& name);
	virtual ~ISystem() = 0;

	const std::string getName() const;

	virtual void processEntity(IEntity* entity) const = 0;

	//virtual onEvent(const Event& event) const;

private:
	const std::string _name;
};

}

#endif // FALCON_ISYSTEM_H
