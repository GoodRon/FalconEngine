#include "ShipStateSystem.h"

#include <SDL_timer.h>

#include <random>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>

#include <firefly/components/State.h>
#include <firefly/components/Position.h>
#include <firefly/components/Visual.h>
#include <firefly/components/Velocity.h>

namespace spacewar {

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
	
	if (componentState->current == "Idle") {
		updateIdle(componentState, componentVisual,
			componentPosition, componentVelocity);
		return;
	}

	if (componentState->current == "Moving") {
		updateMoving(componentState, componentVisual,
			componentPosition, componentVelocity);
		return;
	}

	if (componentState->current == "Hyperspace") {
		updateHyperspace(componentState, componentVisual,
			componentPosition, componentVelocity);
		return;
	}

	if (componentState->current == "Destroyed") {
		updateDestroyed(componentState, componentVisual,
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

	// TODO move strings to some constant place
	const std::string nextState = "Moving";

	state->previous = state->current;
	state->current = nextState;
	state->timepoint = SDL_GetTicks64();

	visual->currentState = nextState;
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

	// TODO move strings to some constant place
	const std::string nextState = "Idle";

	state->previous = state->current;
	state->current = nextState;
	state->timepoint = SDL_GetTicks64();

	visual->currentState = nextState;
}

int randomInt(int min, int max) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(mt);
}

void randomScreenPosition(int width, int height, double& x, double& y) {
	x = static_cast<double>(randomInt(0, width));
	y = static_cast<double>(randomInt(0, height));
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

	// TODO read from a config
	const uint64_t hyperspaceTimeMs = 2000;
	const uint64_t timepoint = SDL_GetTicks64();
	if ((timepoint - state->timepoint) < hyperspaceTimeMs) {
		if (visual->isVisible) {
			visual->isVisible = false;
		}
		return;
	}

	std::string nextState = "Idle";
	if (velocity->acceleration > 0.0) {
		nextState = "Moving";
	}

	state->previous = state->current;
	state->current = nextState;
	state->timepoint = timepoint;

	visual->currentState = nextState;
	visual->isVisible = true;

	// TODO move to a separate func
	const auto renderer = getEngine()->getRenderer();
	auto rect = renderer->getViewport();

	randomScreenPosition(rect.w, rect.h, position->x, position->y);
}

void ShipStateSystem::updateDestroyed(
	firefly::State* state,
	firefly::Visual* visual,
	firefly::Position* position,
	firefly::Velocity* velocity) const {

	if (!state || !visual || !position || !velocity) {
		return;
	}

	// TODO write me
}

}