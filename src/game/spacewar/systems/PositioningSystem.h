/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_POSITIONING_H
#define SW_SYSTEMS_POSITIONING_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Position;
	class Velocity;
}

namespace spacewar {

class PositioningSystem final: public firefly::ISystem {
public:
	PositioningSystem(firefly::Engine* engine);
	~PositioningSystem() override;

	PositioningSystem(const PositioningSystem&) = delete;
	PositioningSystem& operator=(const PositioningSystem&) = delete;

	void update() override;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	void processPosition(
		firefly::Position* position, 
		firefly::Velocity* velocity, 
		uint64_t elapsedMs) const;
};

}

#endif // SW_SYSTEMS_POSITIONING_H
