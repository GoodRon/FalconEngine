#include "MainState.h"

#include "GameStates.h"

#include <firefly/Engine.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>

#include <firefly/events/NativeEvent.h>

namespace spacewar {

MainState::MainState(firefly::Engine* engine):
	firefly::IGameState(engine, GameState::Main) {

	const auto entityManager = engine->getEntityManager();
	const auto prototypes = engine->getEntityPrototypes();

	std::shared_ptr<firefly::Entity> entity;

	entity = prototypes->makeEntity("Background");
	entityManager->addEntity(std::move(entity));

	entity = prototypes->makeEntity("Player_1");
	entityManager->addEntity(std::move(entity));

	entity = prototypes->makeEntity("Player_2");
	entityManager->addEntity(std::move(entity));

	entity = prototypes->makeEntity("Star");
	entityManager->addEntity(std::move(entity));
}

MainState::~MainState() {
}

void MainState::onEnter() {

}

void MainState::onExit() {

}

bool MainState::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {


	return false;
}

}
