#include "StateSystem.h"

#include <SDL_timer.h>

#include <random>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>
#include <firefly/EntityManager.h>

#include <firefly/components/State.h>
#include <firefly/components/Position.h>
#include <firefly/components/Visual.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Lives.h>

#include "StateNames.h"

namespace spacewar {

static int randomInt(int min, int max) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(mt);
}

static void randomScreenPosition(
	int width, int height, double& x, double& y) {

	x = static_cast<double>(randomInt(0, width));
	y = static_cast<double>(randomInt(0, height));
}

static void changeState(
	firefly::State* state, 
	const std::string& nextState) {

	if (!state) {
		return;
	}

	if (state->current == nextState) {
		return;
	}

	state->previous = state->current;
	state->current = nextState;
	state->timepoint = SDL_GetTicks64();
}

static void changeVisualState(
	firefly::Visual* visual, 
	const std::string& nextState) {

	if (!visual) {
		return;
	}

	if (visual->currentState == nextState) {
		return;
	}

	visual->currentState = nextState;
	visual->timepoint = SDL_GetTicks64();

	if (visual->states[nextState].isLooped) {
		visual->states[nextState].isStopped = false;
	}
}

ShipStateSystem::ShipStateSystem(firefly::Engine* engine):
	firefly::ISystem("ShipStateSystem", engine) {

	addRequiredComponent(firefly::State::ComponentName);
	addRequiredComponent(firefly::Position::ComponentName);
	addRequiredComponent(firefly::Visual::ComponentName);
	addRequiredComponent(firefly::Velocity::ComponentName);
}

ShipStateSystem::~ShipStateSystem() {
}

void ShipStateSystem::onUpdate() {
	auto& entities = getEntities();
	for (auto& entity: entities) {
		updateState(entity.second);
	}
}

void ShipStateSystem::updateState(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	auto componentState = entity->getComponent<firefly::State>();
	auto componentPosition = entity->getComponent<firefly::Position>();
	auto componentVisual = entity->getComponent<firefly::Visual>();
	auto componentVelocity = entity->getComponent<firefly::Velocity>();
	
	changeVisualState(componentVisual, componentState->current);

	if (componentState->current == stateNameIdle()) {
		updateIdle(componentState, componentVisual,
			componentPosition, componentVelocity);
		return;
	}

	if (componentState->current == stateNameMoving()) {
		updateMoving(componentState, componentVisual,
			componentPosition, componentVelocity);
		return;
	}

	if (componentState->current == stateNameHyperspace()) {
		updateHyperspace(componentState, componentVisual,
			componentPosition, componentVelocity);
		return;
	}

	if (componentState->current == stateNameDestroyed()) {
		updateDestroyed(entity, componentState, componentVisual,
			componentPosition, componentVelocity);
		return;
	}
}

// TODO improve

void ShipStateSystem::updateIdle(
	firefly::State* state,
	firefly::Visual* visual,
	firefly::Position* position,
	firefly::Velocity* velocity) const {

	if (!state || !visual || !position || !velocity) {
		return;
	}

	const double epsilon = 0.0001;
	if (velocity->acceleration < epsilon) {
		return;
	}

	const std::string nextState = stateNameMoving();
	changeState(state, nextState);
	changeVisualState(visual, nextState);
}

void ShipStateSystem::updateMoving(
	firefly::State* state,
	firefly::Visual* visual,
	firefly::Position* position,
	firefly::Velocity* velocity) const {

	if (!state || !visual || !position || !velocity) {
		return;
	}

	const double epsilon = 0.0001;
	if (velocity->acceleration > epsilon) {
		return;
	}

	const std::string nextState = stateNameIdle();
	changeState(state, nextState);
	changeVisualState(visual, nextState);
}

// TODO turn off velocity & gravity
void ShipStateSystem::updateHyperspace(
	firefly::State* state,
	firefly::Visual* visual,
	firefly::Position* position,
	firefly::Velocity* velocity) const {

	if (!state || !visual || !position || !velocity) {
		return;
	}

	// TODO improve this
	// TODO read from a config
	const uint64_t hyperspaceTimeMs = 2000;
	const uint64_t timepoint = SDL_GetTicks64();
	if ((timepoint - state->timepoint) < hyperspaceTimeMs) {
		if (visual->isVisible) {
			visual->isVisible = false;
		}
		return;
	}

	std::string nextState = stateNameIdle();
	if (velocity->acceleration > 0.0) {
		nextState = stateNameMoving();
	}

	changeState(state, nextState);
	changeVisualState(visual, nextState);

	visual->isVisible = true;

	const auto renderer = getEngine()->getRenderer();
	auto rect = renderer->getViewport();

	randomScreenPosition(rect.w, rect.h, position->x, position->y);
}

void ShipStateSystem::updateDestroyed(
	firefly::Entity* entity,
	firefly::State* state,
	firefly::Visual* visual,
	firefly::Position* position,
	firefly::Velocity* velocity) const {

	if (!entity || !state || !visual || !position || !velocity) {
		return;
	}

	// NOTE awaiting the animation to stop
	if (!visual->states[visual->currentState].isStopped) {
		return;
	}

	const auto lives = entity->getComponent<firefly::Lives>();
	if (lives) {
		lives->currentLives--;
		if (lives->currentLives > 0) {
			// NOTE respawn

			const auto renderer = getEngine()->getRenderer();
			auto rect = renderer->getViewport();
			randomScreenPosition(rect.w, rect.h, position->x, position->y);
			
			velocity->speed = 0.0;
			velocity->acceleration = 0.0;

			const std::string nextState = stateNameIdle();
			changeState(state, nextState);
			changeVisualState(visual, nextState);
			return;
		}
	}

	const auto entityManager = getEngine()->getEntityManager();
	entityManager->removeEntity(entity->getId());
}

}