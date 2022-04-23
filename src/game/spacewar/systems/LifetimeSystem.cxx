#include "LifetimeSystem.h"

#include <forward_list>

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/EntityManager.h>
#include <firefly/Entity.h>
#include <firefly/components/Lifetime.h>

namespace spacewar {

LifetimeSystem::LifetimeSystem(firefly::Engine* engine):
	firefly::ISystem(LifetimeSystem::Name, engine),
	_entityManager(engine->getEntityManager()) {

	addRequiredComponent(firefly::Lifetime::ComponentName);
}

LifetimeSystem::~LifetimeSystem() {
}

void LifetimeSystem::onUpdate() {
	std::forward_list<firefly::EntityID> expiredIds;

	for (auto& entity: getEntities()) {
		if (!entity.second->isActive()) {
			continue;
		}

		if (isEntityExpired(entity.second)) {
			expiredIds.push_front(entity.second->getId());
		}
	}

	for (auto& id: expiredIds) {
		_entityManager->removeEntity(id);
	}
}

bool LifetimeSystem::isEntityExpired(firefly::Entity* entity) const {
	auto lifetime = entity->getComponent<firefly::Lifetime>();
	if (!lifetime) {
		return true;
	}

	if (SDL_GetTicks64() - lifetime->timepoint > lifetime->lifetimeMs) {
		return true;
	}
	return false;
}

}
