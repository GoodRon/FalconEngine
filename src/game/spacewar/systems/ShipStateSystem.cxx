#include "ShipStateSystem.h"

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

	_requiredComponents.push_front(firefly::State::ComponentName);
	_requiredComponents.push_front(firefly::Position::ComponentName);
	_requiredComponents.push_front(firefly::Visual::ComponentName);
	_requiredComponents.push_front(firefly::Velocity::ComponentName);
}

ShipStateSystem::~ShipStateSystem() {
}

void ShipStateSystem::update() {
	const uint64_t timepoint = SDL_GetTicks64();
	const uint64_t elapsedMs = timepoint - _updateTimepoint;
	_updateTimepoint = timepoint;

	for (auto& entity: _entities) {
		updateState(entity.second, elapsedMs);
	}
}

bool ShipStateSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

void ShipStateSystem::updateState(
	firefly::Entity* entity,
	uint64_t elapsedMs) const {

	if (!entity) {
		return;
	}

	auto componentState = static_cast<firefly::State*>(
		entity->getComponent(
			firefly::getComponentId(firefly::State::ComponentName)));

	auto componentPosition = static_cast<firefly::Position*>(
		entity->getComponent(
			firefly::getComponentId(firefly::Position::ComponentName)));

	auto componentVisual = static_cast<firefly::Visual*>(
		entity->getComponent(
			firefly::getComponentId(firefly::Visual::ComponentName)));

	auto componentVelocity = static_cast<firefly::Velocity*>(
		entity->getComponent(
			firefly::getComponentId(firefly::Velocity::ComponentName)));
	
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
	state->timepoint = _updateTimepoint;

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
	state->timepoint = _updateTimepoint;

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
	if ((_updateTimepoint - state->timepoint) < hyperspaceTimeMs) {
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
	state->timepoint = _updateTimepoint;

	visual->currentState = nextState;
	visual->isVisible = true;

	// TODO move to a separate func
	const auto renderer = _engine->getRenderer();
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