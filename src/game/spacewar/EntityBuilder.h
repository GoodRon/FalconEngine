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
	class Entity;
}

namespace spacewar {

class EntityBuilder {
public:
	EntityBuilder(falcon::Engine* engine);
	~EntityBuilder();

	EntityBuilder(EntityBuilder&&) = default;
	EntityBuilder& operator=(EntityBuilder&&) = default;

	std::shared_ptr<falcon::Entity> buildEntity(
		const std::string& jsonConfig);

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

}

#endif // SW_UNIT_BUILDER_H
