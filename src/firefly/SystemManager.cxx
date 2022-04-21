#include "SystemManager.h"

#include "systems/ISystem.h"

namespace firefly {

SystemManager::SystemManager():
	_systems() {
}

SystemManager::~SystemManager() {
}

void SystemManager::addSystem(const std::shared_ptr<ISystem>& system) {
	if (!system) {
		return;
	}

	const auto name = system->getName();
	_systems[name] = system;
}

bool SystemManager::hasSystem(const std::string& name) const {
	if (_systems.find(name) != _systems.end()) {
		return true;
	}
	return false;
}

std::shared_ptr<ISystem> 
SystemManager::getSystem(const std::string& name) {
	if (hasSystem(name)) {
		return nullptr;
	}
	return _systems[name];
}

bool SystemManager::processEvent(
		const std::shared_ptr<IEvent>& event) {
	for (auto& sys: _systems) {
		if (sys.second->processEvent(event)) {
			return true;
		}
	}
	return false;
}

void SystemManager::clear() {
	_systems.clear();
}

}
