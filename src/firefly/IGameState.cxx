#include "IGameState.h"

#include "Engine.h"
#include "Entity.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "systems/ISystem.h"

namespace firefly {

IGameState::IGameState(
	Engine* engine, 
	int id):
	_engine(engine),
	_id(id),
	_isInit(false),
	_objectIds(),
	_systemNames() {
}

IGameState::~IGameState() {
	destroySystems();
	destroyObjects();
}

int IGameState::getId() const {
	return _id;
}

void IGameState::init() {
	if (_isInit) {
		return;
	}

	buildObjects();
	buildSystems();
}

bool IGameState::isInit() const {
	return _isInit;
}

void IGameState::onEnter() {
}

void IGameState::onExit() {
}

bool IGameState::onEvent(
	const std::shared_ptr<IEvent>& event) {
	return false;
}

Engine* IGameState::getEngine() const {
	return _engine;
}

void IGameState::buildObjects() {
}

void IGameState::setObjectIds(
	std::forward_list<EntityID>&& objectIds) {
	if (!_objectIds.empty()) {
		destroyObjects();
	}

	_objectIds = std::move(objectIds);
}

void IGameState::destroyObjects() {
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();

	for (auto& id: _objectIds) {
		entityManager->removeEntity(id);
	}
	_objectIds.clear();
}

void IGameState::setObjectsActive(bool isActive) const {
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();

	std::shared_ptr<firefly::Entity> entity;
	for (auto& id: _objectIds) {
		entity = std::move(entityManager->getEntity(id));
		entity->setActive(isActive);
	}
}

void IGameState::buildSystems() {
}

void IGameState::setSystemNames(
	std::forward_list<std::string>&& systemNames) {
	if (!_systemNames.empty()) {
		destroyObjects();
	}

	_systemNames = std::move(systemNames);
}

void IGameState::destroySystems() {
	const auto engine = getEngine();
	const auto systemManager = engine->getSystemManager();

	for (auto& systemName: _systemNames) {
		systemManager->removeSystem(systemName);
	}
	_systemNames.clear();
}

void IGameState::setSystemsActive(bool isActive) const {
	const auto engine = getEngine();
	const auto systemManager = engine->getSystemManager();

	std::shared_ptr<firefly::ISystem> sys;
	for (auto& systemName: _systemNames) {
		sys = std::move(systemManager->getSystem(systemName));
		if (sys) {
			sys->setActive(isActive);
		}
	}
}

}
