/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_LIFETIME_H
#define SW_SYSTEMS_LIFETIME_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Entity;
}

namespace spacewar {

class LifetimeSystem final: public firefly::ISystem {
public:
	LifetimeSystem(firefly::Engine* engine);
	~LifetimeSystem() override;

	LifetimeSystem(const LifetimeSystem&) = delete;
	LifetimeSystem& operator=(const LifetimeSystem&) = delete;

	void onUpdate() override;
	
private:
	bool isEntityExpired(firefly::Entity* entity) const;
};

}

#endif // SW_SYSTEMS_LIFETIME_H
