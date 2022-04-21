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

void SystemManager::registerEntity(Entity* entity) {
	for (auto& sys: _systems) {
		sys.second->registerEntity(entity);
	}
}

void SystemManager::unregisterEntity(EntityID id) {
	for (auto& sys: _systems) {
		sys.second->unregisterEntity(id);
	}
}

void SystemManager::updateSystems() {
	for (auto& sys: _systems) {
		if (sys.second->isActive()) {
			sys.second->update();
		}
	}
}

bool SystemManager::onEvent(
		const std::shared_ptr<IEvent>& event) {
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
