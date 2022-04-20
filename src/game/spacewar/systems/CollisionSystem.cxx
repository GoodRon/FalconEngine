#include "SollisionSystem.h"

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/components/RoundCollidable.h>

namespace spacewar {

CollisionSystem::CollisionSystem(firefly::Engine* engine):
	firefly::ISystem("CollisionSystem", engine) {

	_requiredComponents.push_front(firefly::RoundCollidable::ComponentName);
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::update() {

	 

	for (auto& entity: _entities) {
		
	}
}

bool CollisionSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

}
