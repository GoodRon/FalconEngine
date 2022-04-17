#include "RenderingSystem.h"

#include "IComponent.h"
#include "Entity.h"

namespace falcon {

RenderingSystem::RenderingSystem():
	ISystem("Rendering"),
	_visualComponentId(getComponentId("Visual")) {
}

RenderingSystem::~RenderingSystem() {
}

bool RenderingSystem::onEvent(
    const std::shared_ptr<IEvent>& event) const {

	// TODO write me
	return true;
}

bool RenderingSystem::checkComponents(Entity* entity) const {
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