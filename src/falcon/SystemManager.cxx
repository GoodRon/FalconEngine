#include "SystemManager.h"

#include "ISystem.h"

namespace falcon {

SystemManager::SystemManager():
	_systems() {
}

SystemManager::~SystemManager() {
}

void SystemManager::addSystem(std::unique_ptr<ISystem>&& system) {
	if (!system) {
		return;
	}

	const auto name = system->getName();
	_systems[name] = std::move(system);
}

bool SystemManager::hasSystem(const std::string& name) const {
	if (_systems.find(name) != _systems.end()) {
		return true;
	}
	return false;
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
