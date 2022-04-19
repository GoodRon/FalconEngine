#include "IComponent.h"

#include "EngineException.h"

#include <unordered_map>

namespace firefly {

static std::unordered_map<std::string, ComponentID> componentRegistry;
static ComponentID nextComponentdId = 0;

ComponentID getComponentId(const std::string& name) {
	if (componentRegistry.find(name) != componentRegistry.end()) {
		return componentRegistry[name];
	}

	auto id = nextComponentdId++;
	componentRegistry[name] = id;
	return id;
}

IComponent::IComponent(const std::string& name):
	_name(name),
	_id(getComponentId(name)) {
}

const std::string IComponent::getName() const {
	return _name;
}

ComponentID IComponent::getId() const {
	return _id;
}

}
