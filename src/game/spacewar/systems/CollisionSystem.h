/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_COLLISION_H
#define SW_SYSTEMS_COLLISION_H

#include <firefly/systems/ISystem.h>

namespace spacewar {

class CollisionSystem final: public firefly::ISystem {
public:
	CollisionSystem(firefly::Engine* engine);
	~CollisionSystem() override;

	CollisionSystem(const CollisionSystem&) = delete;
	CollisionSystem& operator=(const CollisionSystem&) = delete;

	void update() override;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;
};

}

#endif // SW_SYSTEMS_COLLISION_H
