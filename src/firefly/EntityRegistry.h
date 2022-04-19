/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ENTITY_REGISTRY_H
#define FIREFLY_ENTITY_REGISTRY_H

#include <memory>
#include <unordered_map>

namespace firefly {

class Entity;

class EntityRegistry {
public:
	EntityRegistry();
	~EntityRegistry() = default;

	EntityRegistry(const EntityRegistry&) = delete;
	EntityRegistry& operator=(const EntityRegistry&) = delete;

	bool registerEntity(const std::string& name, 
		std::unique_ptr<Entity>& prototype);

	std::shared_ptr<Entity> makeEntity(const std::string& name);

	void clear();

private:
	std::unordered_map<std::string, std::unique_ptr<Entity>> _prototypes;
};

}

#endif // FIREFLY_ENTITY_REGISTRY_H
