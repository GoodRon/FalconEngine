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

	ObjectBuilder(ObjectBuilder&&) = default;
	ObjectBuilder& operator=(ObjectBuilder&&) = default;

	std::shared_ptr<falcon::IGameObject> buildObject(
		const std::string& jsonConfig);

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

}

#endif // SW_UNIT_BUILDER_H
