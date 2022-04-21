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
#include <firefly/components/Gravity.h>
#include <firefly/components/Lives.h>
#include <firefly/components/RoundCollidable.h>

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

static void setEntityReactivenes(
	firefly::Entity* entity, bool isReactive) {

	const auto velocity = entity->getComponent<firefly::Velocity>();
	if (velocity) {
		velocity->isActive = isReactive;
	}

	const auto gravity = entity->getComponent<firefly::Gravity>();
	if (gravity) {
		gravity->isActive = isReactive;
	}

	const auto collidable = entity->getComponent<firefly::RoundCollidable>();
	if (collidable) {
		collidable->isActive = isReactive;
	}
}

StateSystem::StateSystem(firefly::Engine* engine):
	firefly::ISystem("StateSystem", engine) {

	addRequiredComponent(firefly::State::ComponentName);
	addRequiredComponent(firefly::Position::ComponentName);
	addRequiredComponent(firefly::Visual::ComponentName);
	addRequiredComponent(firefly::Velocity::ComponentName);
}

StateSystem::~StateSystem() {
}

void StateSystem::onUpdate() {
	auto& entities = getEntities();
	for (auto& entity: entities) {
		updateState(entity.second);
	}
}

void StateSystem::updateState(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	const auto state = entity->getComponent<firefly::State>();
	const auto visual = entity->getComponent<firefly::Visual>();
	
	changeVisualState(visual, state->current);

	if (state->current == stateNameIdle()) {
		updateIdle(entity);
		return;
	}

	if (state->current == stateNameMoving()) {
		updateMoving(entity);
		return;
	}

	if (state->current == stateNameHyperspace()) {
		updateHyperspace(entity);
		return;
	}

	if (state->current == stateNameDestroyed()) {
		updateDestroyed(entity);
		return;
	}
}

// TODO improve

void StateSystem::updateIdle(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	const auto state = entity->getComponent<firefly::State>();
	const auto velocity = entity->getComponent<firefly::Velocity>();
	const auto visual = entity->getComponent<firefly::Visual>();

	if (!state || !visual || !velocity) {
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

void StateSystem::updateMoving(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	const auto state = entity->getComponent<firefly::State>();
	const auto velocity = entity->getComponent<firefly::Velocity>();
	const auto visual = entity->getComponent<firefly::Visual>();

	if (!state || !visual || !velocity) {
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
void StateSystem::updateHyperspace(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	const auto state = entity->getComponent<firefly::State>();
	const auto velocity = entity->getComponent<firefly::Velocity>();
	const auto visual = entity->getComponent<firefly::Visual>();
	const auto position = entity->getComponent<firefly::Position>();

	if (!state || !visual || !position || !velocity) {
		return;
	}

	// TODO improve this
	// TODO read from a config
	const uint64_t hyperspaceTimeMs = 2000;
	const uint64_t timepoint = SDL_GetTicks64();

	// NOTE in hyberspace
	if ((timepoint - state->timepoint) < hyperspaceTimeMs) {
		setEntityReactivenes(entity, false);

		if (visual->isVisible) {
			visual->isVisible = false;
		}
		return;
	}

	setEntityReactivenes(entity, true);

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

void StateSystem::updateDestroyed(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	setEntityReactivenes(entity, false);

	const auto state = entity->getComponent<firefly::State>();
	const auto velocity = entity->getComponent<firefly::Velocity>();
	const auto visual = entity->getComponent<firefly::Visual>();
	const auto position = entity->getComponent<firefly::Position>();

	if (!state || !visual || !position || !velocity) {
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

			setEntityReactivenes(entity, true);

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