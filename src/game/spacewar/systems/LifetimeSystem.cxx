#include "LifetimeSystem.h"

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

	firefly::Entity* entity = nullptr;
	auto objectManager = _engine->getObjectManager();

	auto& it = _entities.begin();
	while (it != _entities.end()) {
		entity = it->second;

		if (!entity) {
			++it;
			continue;
		}

		auto lifetime = entity->getComponent<firefly::Lifetime>();
		if (!lifetime) {
			++it;
			continue;
		}

		if (_updateTimepoint - lifetime->timepoint < lifetime->lifetimeMs) {
			++it;
			continue;
		}

		it = _entities.erase(it);

		objectManager->unregisterObject(entity->getId());
	}
}

bool LifetimeSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

}
