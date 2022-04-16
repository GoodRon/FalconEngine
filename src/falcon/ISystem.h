/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ISYSTEM_H
#define FALCON_ISYSTEM_H

#include <string>
#include <memory>

namespace falcon {

class IEvent;

class ISystem {
public:
	ISystem(const std::string& name): _name(name) {}
	virtual ~ISystem() {}

	const std::string getName() const {
		return _name;
	}

	virtual void processEntity(
		const std::shared_ptr<IEvent>& entity) const = 0;

	virtual bool onEvent(
		const std::shared_ptr<IEvent>& event) const = 0;

private:
	const std::string _name;
};

}

#endif // FALCON_ISYSTEM_H
