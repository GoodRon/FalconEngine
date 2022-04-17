#include "AnimationSystem.h"

#include "ComponentRegistry.h"
#include "IEntity.h"

namespace falcon {

AnimationSystem::AnimationSystem():
	ISystem("Animation"),
	_animationComponentId(-1) {

}

AnimationSystem::~AnimationSystem() {
}

bool AnimationSystem::resolveComponentIDs(
    ComponentRegistry* componentRegistry) {

	if (isReady()) {
		return true;
	}

	if (!componentRegistry) {
		return false;
	}

	auto id = componentRegistry->findComponentID("Visual");
	if (id < 0) {
		return false;
	}

	_animationComponentId = id;

	_isReady = true;

	return true;
}

bool AnimationSystem::onEvent(
    const std::shared_ptr<IEvent>& event) const {

	// TODO write me
	return true;
}

bool AnimationSystem::checkComponents(IEntity* entity) const {
	if (!isReady()) {
		return false;
	}

	if (!entity) {
		return false;
	}

	auto component = entity->getComponent(_animationComponentId);
	if (!component) {
		return false;
	}
	return true;
}

}