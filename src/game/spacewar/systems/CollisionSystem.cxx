#include "CollisionSystem.h"

#include <unordered_set>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/Renderer.h>
#include <firefly/EntityManager.h>
#include <firefly/components/RoundCollidable.h>
#include <firefly/components/Position.h>

#include "misc/Quadtree.h"

namespace spacewar {

CollisionSystem::CollisionSystem(firefly::Engine* engine):
	firefly::ISystem("CollisionSystem", engine),
	_qauadtree() {

	addRequiredComponent(firefly::RoundCollidable::ComponentName);
	addRequiredComponent(firefly::Position::ComponentName);

	auto renderer = engine->getRenderer();
	_qauadtree.reset(new EntityQuadtree(renderer->getViewport()));
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::onUpdate() {

	auto& entities = getEntities();
	if (entities.empty()) {
		return;
	}

	_qauadtree->clear();

	for (auto& entity: entities) {
		_qauadtree->insert(entity.second);
	}

	std::unordered_set<firefly::EntityID> destroyedIds;

	for (auto& entityIt: entities) {
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

	auto entityManager = getEngine()->getEntityManager();
	for (auto& id: destroyedIds) {
		entityManager->removeEntity(id);
	}
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
