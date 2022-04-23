#include "SystemManager.h"

#include "systems/ISystem.h"

namespace firefly {

SystemManager::SystemManager():
	_systems() {
}

SystemManager::~SystemManager() {
}

bool SystemManager::addSystem(const std::shared_ptr<ISystem>& system) {
	if (!system) {
		return false;
	}

	const auto name = system->getName();
	if (hasSystem(name)) {
		return false;
	}
	_systems[name] = system;
	return true;
}

void SystemManager::removeSystem(const std::string& name) {
	if (hasSystem(name)) {
		return;
	}
	_systems.erase(name);
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
