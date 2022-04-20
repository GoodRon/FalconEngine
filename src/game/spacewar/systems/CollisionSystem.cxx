#include "CollisionSystem.h"

#include <unordered_set>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/ObjectManager.h>
#include <firefly/Renderer.h>
#include <firefly/components/RoundCollidable.h>
#include <firefly/components/Position.h>

#include "Quadtree.h"

namespace spacewar {

CollisionSystem::CollisionSystem(firefly::Engine* engine):
	firefly::ISystem("CollisionSystem", engine),
	_qauadtree() {

	_requiredComponents.push_front(firefly::RoundCollidable::ComponentName);
	_requiredComponents.push_front(firefly::Position::ComponentName);

	auto renderer = engine->getRenderer();
	_qauadtree.reset(new EntityQuadtree(renderer->getViewport()));
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::update() {

	if (_entities.empty()) {
		return;
	}

	_qauadtree->clear();

	for (auto& entity: _entities) {
		_qauadtree->insert(entity.second);
	}

	std::unordered_set<firefly::EntityID> destroyedIds;

	for (auto& entityIt: _entities) {
		auto entity = entityIt.second;

		auto positionLeft = entity->getComponent<firefly::Position>();
		auto collidableLeft = entity->getComponent<firefly::RoundCollidable>();

		auto nearestEntities = _qauadtree->retrieve(positionLeft->toRect());
		for (auto& nearestEntity: nearestEntities) {
			if (entity == nearestEntity) {
				continue;
			}

			auto positionRight = nearestEntity->getComponent<firefly::Position>();
			auto collidableRight = nearestEntity->getComponent<firefly::RoundCollidable>();

			if (isCollided(collidableLeft, positionLeft,
				collidableRight, positionRight)) {

				if (collidableRight->isDestructable) {
					destroyedIds.insert(nearestEntity->getId());
				}
			}
		}
	}

	auto objectManager = _engine->getObjectManager();
	for (auto& id: destroyedIds) {
		objectManager->unregisterObject(id);
	}
}

bool CollisionSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

bool CollisionSystem::isCollided(
		firefly::RoundCollidable* collidableLeft,
		firefly::Position* positionLeft,
		firefly::RoundCollidable* collidableRight,
		firefly::Position* positionRigth) const {

	if (!collidableLeft || !positionLeft ||
		!collidableRight || !positionRigth) {
		return false;
	}

	// TODO fix the center!
	const double distanceX = positionLeft->x - positionRigth->x;
	const double dsistanceY = positionLeft->y - positionRigth->y;
	const double squaredDistance = distanceX * distanceX 
		+ dsistanceY * dsistanceY;
	const double minCollisionDistance = collidableLeft->collidableRadius 
		+ collidableRight->collidableRadius;

	if (squaredDistance < minCollisionDistance * minCollisionDistance) {
		return true;
	}
	return false;
}

}
