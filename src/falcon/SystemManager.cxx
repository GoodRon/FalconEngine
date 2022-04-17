#include "SystemManager.h"

#include "ISystem.h"

namespace falcon {

SystemManager::SystemManager():
	_systems() {
}

SystemManager::~SystemManager() {
}

bool SystemManager::hasSystem(const std::string& name) const {
	if (_systems.find(name) != _systems.end()) {
		return true;
	}
	return false;
}

bool SystemManager::onEvent(
		const std::shared_ptr<IEvent>& event) const {
	for (auto& sys: _systems) {
		if (sys.second->onEvent(event)) {
			return true;
		}
	}
	return false;
}

void SystemManager::clear() {
	_systems.clear();
}

}
