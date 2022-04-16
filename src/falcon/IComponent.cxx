#include "IComponent.h"

namespace falcon {

IComponent::IComponent(const std::string& name):
	_name(name),
	_id(-1) {

}

IComponent::~IComponent() {
}

const std::string IComponent::getName() const {
	return _name;
}

void IComponent::setId(ComponentID id) {
	_id = id;
}

ComponentID IComponent::getId() const {
	return _id;
}

}
