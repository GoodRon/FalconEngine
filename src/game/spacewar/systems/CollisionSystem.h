/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_COLLISION_H
#define SW_SYSTEMS_COLLISION_H

#include <memory>

#include <firefly/systems/ISystem.h>

namespace firefly {
	class RoundCollidable;
	class Position;
}

namespace spacewar {

class EntityQuadtree;

class CollisionSystem final: public firefly::ISystem {
public:
	CollisionSystem(firefly::Engine* engine);
	~CollisionSystem() override;

	CollisionSystem(const CollisionSystem&) = delete;
	CollisionSystem& operator=(const CollisionSystem&) = delete;

	void update() override;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	bool isCollided(
		firefly::RoundCollidable* collidableLeft,
		firefly::Position* positionLeft,
		firefly::RoundCollidable* collidableRight,
		firefly::Position* positionRigth) const;

private:
	std::unique_ptr<EntityQuadtree> _qauadtree;
};

}

#endif // SW_SYSTEMS_COLLISION_H
