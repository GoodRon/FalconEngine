/*
 * Copyright (c) 2017, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef WORLD_BUILDER_H
#define WORLD_BUILDER_H

#include <memory>
#include <string>
#include <map>

class ResourceManager;
class Unit;
// class UnitBuilder;
class IAnimation;

std::shared_ptr<Unit> UnitPointer;

namespace engine {
	class WorldBuilder {
	public:
		WorldBuilder(ResourceManager* resourceManager);

		~WorldBuilder();

		UnitPointer buildUnit(const std::string& jsonRecipe);

	private:
		ResourceManager* m_resourceManager;
		// std::map<std::string, UnitBuilder*> m_unitBuilders;
	}
}

#endif // WORLD_BUILDER_H