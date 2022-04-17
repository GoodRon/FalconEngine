/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_UNIT_BUILDER_H
#define SW_UNIT_BUILDER_H

#include <memory>
#include <string>

namespace falcon {
	class Engine;
	class IGameObject;
}

namespace spacewar {

class ObjectBuilder {
public:
	ObjectBuilder(falcon::Engine* engine);
	~ObjectBuilder();

	std::shared_ptr<falcon::IGameObject> buildShip(const std::string& jsonConfig) const;

private:
	falcon::Engine* const _engine;
};

}

#endif // SW_UNIT_BUILDER_H
