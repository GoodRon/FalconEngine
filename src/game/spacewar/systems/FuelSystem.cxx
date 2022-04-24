#include "FuelSystem.h"

#include <SDL_timer.h>

#include <firefly/Entity.h>

#include <firefly/events/SetFuelEvent.h>

#include <firefly/components/Fuel.h>
#include <firefly/components/State.h>

#include "ObjectStates.h"

namespace spacewar {

FuelSystem::FuelSystem(firefly::Engine* engine):
	firefly::ISystem(FuelSystem::Name, engine) {

	addRequiredComponent(firefly::Fuel::ComponentName);
	addRequiredComponent(firefly::State::ComponentName);
}

FuelSystem::~FuelSystem() {
}

bool FuelSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	switch (event->getType()) {
	case firefly::EventType::SetFuel: {
		const auto setFuelEvent = 
			static_cast<firefly::SetFuelEvent*>(event.get());
		if (!setFuelEvent) {
			return false;
		}

		setFuel(setFuelEvent->getId(),
			setFuelEvent->getCurrent(),
			setFuelEvent->getMax());
		return true;
	} break;

	default:
		break;
	}

	return false;
}

void FuelSystem::onUpdate() {
	for (auto& entity: getEntities()) {
		if (!entity.second->isActive()) {
			continue;
		}

		const auto fuel = entity.second->getComponent<firefly::Fuel>();
		const auto state = entity.second->getComponent<firefly::State>();

		if (state->current == ObjectState::Moving) {
			updateFuel(fuel);
		}
	}
}

void FuelSystem::updateFuel(firefly::Fuel* fuel) const {
	if (!fuel) {
		return;
	}

	constexpr double epsilon = 0.00001;
	if (fuel->current < epsilon) {
		return;
	}

	// TODO read from a config
	constexpr double fuelConsumption = 10.0;

	fuel->current -= fuelConsumption * getElapsedMs() / 1000.0;
	if (fuel->current < epsilon) {
		fuel->current = 0.0;
	}
}

void FuelSystem::setFuel(
	firefly::EntityID id, double current, double max) const {

	const auto entity = getEntity(id);
	if (!entity) {
		return;
	}

	const auto fuel = entity->getComponent<firefly::Fuel>();
	if (!fuel) {
		return;
	}

	fuel->current = current;
	
	constexpr double epsilon = 0.00001;
	if (fuel->max > epsilon && fuel->current > fuel->max) {
		fuel->current = fuel->max;
	}
}

}
