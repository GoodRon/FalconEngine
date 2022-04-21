#include "LifetimeSystem.h"

#include <forward_list>

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/ObjectManager.h>
#include <firefly/Entity.h>
#include <firefly/components/Lifetime.h>

namespace spacewar {

LifetimeSystem::LifetimeSystem(firefly::Engine* engine):
	firefly::ISystem("LifetimeSystem", engine) {

	addRequiredComponent(firefly::Lifetime::ComponentName);
}

LifetimeSystem::~LifetimeSystem() {
}

void LifetimeSystem::onUpdate() {
	std::forward_list<firefly::EntityID> expiredIds;

	auto& entities = getEntities();
	for (auto& entity: entities) {
		if (isEntityExpired(entity.second)) {
			expiredIds.push_front(entity.second->getId());
		}
	}

	auto objectManager = getEngine()->getObjectManager();
	for (auto& id: expiredIds) {
		objectManager->unregisterObject(id);
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
