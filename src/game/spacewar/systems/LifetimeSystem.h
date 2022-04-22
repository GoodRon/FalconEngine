/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_LIFETIME_H
#define SW_SYSTEMS_LIFETIME_H

#include <firefly/systems/ISystem.h>
#include <firefly/Types.h>

namespace firefly {
	class Entity;
	class EntityManager;
}

namespace spacewar {

class LifetimeSystem final: public firefly::ISystem {
public:
	LifetimeSystem(firefly::Engine* engine);
	~LifetimeSystem() override;

	LifetimeSystem(const LifetimeSystem&) = delete;
	LifetimeSystem& operator=(const LifetimeSystem&) = delete;
	
private:
	void onUpdate() override;
	bool isEntityExpired(firefly::Entity* entity) const;

private:
	firefly::EntityManager* _entityManager;
};

}

#endif // SW_SYSTEMS_LIFETIME_H
