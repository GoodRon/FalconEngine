#include "MainState.h"

#include "GameStates.h"

#include <firefly/Engine.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/SystemManager.h>
#include <firefly/Entity.h>

#include <firefly/systems/ISystem.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/components/ShipControls.h>

#include "SystemBuilder.h"

#include "systems/ShipControlSystem.h"
#include "systems/PositioningSystem.h"
#include "systems/GravitationalSystem.h"
#include "systems/StateSystem.h"
#include "systems/LifetimeSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/VelocitySystem.h"
#include "systems/RespawnSystem.h"

namespace spacewar {

static void setControls(firefly::Entity* entity,
	int keyCodeUp, int keyCodeDown, 
	int keyCodeLeft, int keyCodeRight) {

	if (!entity) {
		return;
	}

	const auto controls = 
		entity->getComponent<firefly::ShipControls>();
	if (!controls) {
		return;
	}

	controls->keyCodeUp = keyCodeUp;
	controls->keyCodeDown = keyCodeDown;
	controls->keyCodeLeft = keyCodeLeft;
	controls->keyCodeRight = keyCodeRight;
}

MainState::MainState(firefly::Engine* engine):
	firefly::IGameState(engine, GameState::Main),
	_systemNames(),
	_objectIds() {
}

MainState::~MainState() {
}

void MainState::onEnter() {
	constexpr bool isActive = true;
	setObjectsActive(isActive);
	setSystemsActive(isActive);
}

void MainState::onExit() {
	constexpr bool isActive = false;
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

	// TODO write it

	return false;
}

void MainState::buildObjects() {
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();
	const auto prototypes = engine->getEntityPrototypes();

	// TODO read form a config
	const std::forward_list<std::string> entityNames{
		"Player_1", "Player_2", "Star", "Background"
	};
	std::forward_list<firefly::EntityID> ids;

	std::shared_ptr<firefly::Entity> entity;
	for (auto& name: entityNames) {
		entity = std::move(prototypes->makeEntity(name));
		if (!entity) {
			continue;
		}

		entity->setActive(false);
		ids.push_front(entity->getId());

		if (name == "Player_1") {
			setControls(entity.get(), SDLK_w, SDLK_s,
				SDLK_a, SDLK_d);
		}

		if (name == "Player_2") {
			setControls(entity.get(), SDLK_KP_8, SDLK_KP_5,
				SDLK_KP_4, SDLK_KP_6);
		}

		entityManager->addEntity(std::move(entity));
	}

	setObjectIds(std::move(ids));
}

void MainState::buildSystems() {
	const auto engine = getEngine();
	const auto systemManager = engine->getSystemManager();

	// TODO read form a config
	std::forward_list<std::string> systemNames{
		CollisionSystem::Name,
		GravitationalSystem::Name,
		LifetimeSystem::Name,
		PositioningSystem::Name,
		RespawnSystem::Name,
		ShipControlSystem::Name,
		StateSystem::Name,
		VelocitySystem::Name
	};

	std::shared_ptr<firefly::ISystem> system;
	for (auto& name: systemNames) {
		system = std::move(buidSystem(name, engine));
		_systemNames.push_front(name);
		systemManager->addSystem(std::move(system));
	}

	setSystemNames(std::move(systemNames));
}

}
