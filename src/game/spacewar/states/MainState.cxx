#include "MainState.h"

#include "GameStates.h"

#include <firefly/Engine.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/SystemManager.h>
#include <firefly/Entity.h>
#include <firefly/events/NativeEvent.h>

#include "systems/PlayerControlSystem.h"
#include "systems/PositioningSystem.h"
#include "systems/GravitationalSystem.h"
#include "systems/StateSystem.h"
#include "systems/LifetimeSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/VelocitySystem.h"
#include "systems/RespawnSystem.h"

#include <firefly/events/NativeEvent.h>

namespace spacewar {

MainState::MainState(firefly::Engine* engine):
	firefly::IGameState(engine, GameState::Main),
	_systemNames(),
	_objectIds() {

	buildObjects();
	buildSystems();
}

MainState::~MainState() {
	destroySystems();
	destroyObjects();
}

void MainState::onEnter() {
	const bool isActive = true;
	setObjectsActive(isActive);
	setSystemsActive(isActive);
}

void MainState::onExit() {
	const bool isActive = false;
	setObjectsActive(isActive);
	setSystemsActive(isActive);
}

bool MainState::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	if (!event) {
		return false;
	}

	if (event->getType() != firefly::EventType::Native) {
		return false;
	}

	const auto nativeEvent = 
			static_cast<firefly::NativeEvent*>(event.get());

	const auto sdlEvent = nativeEvent->getSDLEvent();
	if (sdlEvent.type && sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
		// NOTE exit the game
		getEngine()->stop();
		return true;
	}

	return false;
}

void MainState::buildObjects() {
	// TODO make a loop?
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();
	const auto prototypes = engine->getEntityPrototypes();

	std::shared_ptr<firefly::Entity> entity;

	entity = std::move(prototypes->makeEntity("Player_1"));
	entity->setActive(false);
	_objectIds.push_front(entity->getId());
	entityManager->addEntity(std::move(entity));

	entity = std::move(prototypes->makeEntity("Player_2"));
	entity->setActive(false);
	_objectIds.push_front(entity->getId());
	entityManager->addEntity(std::move(entity));

	entity = std::move(prototypes->makeEntity("Star"));
	entity->setActive(false);
	_objectIds.push_front(entity->getId());
	entityManager->addEntity(std::move(entity));

	entity = std::move(prototypes->makeEntity("Background"));
	entity->setActive(false);
	_objectIds.push_front(entity->getId());
	entityManager->addEntity(std::move(entity));
}

void MainState::destroyObjects() {
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();

	for (auto& id: _objectIds) {
		entityManager->removeEntity(id);
	}
}

void MainState::setObjectsActive(bool isActive) {
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();

	std::shared_ptr<firefly::Entity> entity;
	for (auto& id: _objectIds) {
		entity = std::move(entityManager->getEntity(id));
		entity->setActive(isActive);
	}
}

void MainState::buildSystems() {
	// TODO make a loop?
	const auto engine = getEngine();
	const auto systemManager = engine->getSystemManager();

	std::shared_ptr<PlayerControlSystem> playerControl;

	playerControl.reset(new PlayerControlSystem(engine, 1, "Player 1"));
	_systemNames.push_front(playerControl->getName());

	playerControl->setKeyCodes(SDLK_w, SDLK_a, SDLK_s, SDLK_d);
	systemManager->addSystem(std::move(playerControl));

	playerControl.reset(new PlayerControlSystem(engine, 2, "Player 2"));
	_systemNames.push_front(playerControl->getName());

	playerControl->setKeyCodes(SDLK_KP_8, SDLK_KP_4, 
		SDLK_KP_5, SDLK_KP_6);
	systemManager->addSystem(std::move(playerControl));

	std::shared_ptr<firefly::ISystem> systemPtr;

	systemPtr.reset(new VelocitySystem(engine));
	_systemNames.push_front(systemPtr->getName());
	systemManager->addSystem(std::move(systemPtr));

	systemPtr.reset(new GravitationalSystem(engine));
	_systemNames.push_front(systemPtr->getName());
	systemManager->addSystem(std::move(systemPtr));

	systemPtr.reset(new PositioningSystem(engine));
	_systemNames.push_front(systemPtr->getName());
	systemManager->addSystem(std::move(systemPtr));

	systemPtr.reset(new StateSystem(engine));
	_systemNames.push_front(systemPtr->getName());
	systemManager->addSystem(std::move(systemPtr));
		
	systemPtr.reset(new LifetimeSystem(engine));
	_systemNames.push_front(systemPtr->getName());
	systemManager->addSystem(std::move(systemPtr));

	systemPtr.reset(new CollisionSystem(engine));
	_systemNames.push_front(systemPtr->getName());
	systemManager->addSystem(std::move(systemPtr));

	systemPtr.reset(new RespawnSystem(engine));
	_systemNames.push_front(systemPtr->getName());
	systemManager->addSystem(std::move(systemPtr));
}

void MainState::destroySystems() {
	const auto engine = getEngine();
	const auto systemManager = engine->getSystemManager();

	for (auto& systemName: _systemNames) {
		systemManager->removeSystem(systemName);
	}
}

void MainState::setSystemsActive(bool isActive) {
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
