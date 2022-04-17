#include "RenderingSystem.h"

#include "ComponentRegistry.h"
#include "Entity.h"

namespace falcon {

RenderingSystem::RenderingSystem():
	ISystem("Rendering"),
	_visualComponentId(-1) {

}

RenderingSystem::~RenderingSystem() {
}

bool RenderingSystem::resolveComponentIDs(
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

	_visualComponentId = id;

	_isReady = true;

	return true;
}

bool RenderingSystem::onEvent(
    const std::shared_ptr<IEvent>& event) const {

	// TODO write me
	return true;
}

bool RenderingSystem::checkComponents(Entity* entity) const {
	if (!isReady()) {
		return false;
	}

	if (!entity) {
		return false;
	}

	auto component = entity->getComponent(_visualComponentId);
	if (!component) {
		return false;
	}
	return true;
}

}