/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_SHIP_STATE_H
#define SW_SYSTEMS_SHIP_STATE_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class State;
	class Position;
	class Visual;
	class Velocity;
}

namespace spacewar {

class ShipStateSystem final: public firefly::ISystem {
public:
	ShipStateSystem(firefly::Engine* engine);
	~ShipStateSystem() override;

	ShipStateSystem(const ShipStateSystem&) = delete;
	ShipStateSystem& operator=(const ShipStateSystem&) = delete;

	void update() override;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	void updateState(
		firefly::Entity* entity,
		uint64_t elapsedMs) const;

	void updateIdle(
		firefly::State* state,
		firefly::Visual* visual,
		firefly::Position* position,
		firefly::Velocity* velocity) const;

	void updateMoving(
		firefly::State* state,
		firefly::Visual* visual,
		firefly::Position* position,
		firefly::Velocity* velocity) const;

	void updateHyperspace(
		firefly::State* state,
		firefly::Visual* visual,
		firefly::Position* position,
		firefly::Velocity* velocity) const;

	void updateDestroyed(
		firefly::State* state,
		firefly::Visual* visual,
		firefly::Position* position,
		firefly::Velocity* velocity) const;
};

}

#endif // SW_SYSTEMS_SHIP_STATE_H
