#include "LifetimeSystem.h"

#include <forward_list>

#include <firefly/Engine.h>
#include <firefly/ObjectManager.h>
#include <firefly/Entity.h>
#include <firefly/components/Lifetime.h>

namespace spacewar {

LifetimeSystem::LifetimeSystem(firefly::Engine* engine):
	firefly::ISystem("LifetimeSystem", engine) {

	_requiredComponents.push_front(firefly::Lifetime::ComponentName);
}

LifetimeSystem::~LifetimeSystem() {
}

void LifetimeSystem::update() {
	const uint64_t timepoint = SDL_GetTicks64();
	const uint64_t elapsedMs = timepoint - _updateTimepoint;
	_updateTimepoint = timepoint;

	std::forward_list<firefly::EntityID> expiredIds;

	for (auto& entity: _entities) {
		if (isEntityExpired(entity.second)) {
			expiredIds.push_front(entity.second->getId());
		}
	}

	auto objectManager = _engine->getObjectManager();
	for (auto& id: expiredIds) {
		objectManager->unregisterObject(id);
	}
}

bool LifetimeSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

bool LifetimeSystem::isEntityExpired(firefly::Entity* entity) const {
	auto lifetime = entity->getComponent<firefly::Lifetime>();
	if (!lifetime) {
		return true;
	}

	if (_updateTimepoint - lifetime->timepoint > lifetime->lifetimeMs) {
		return true;
	}
	return false;
}

}
