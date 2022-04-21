/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_VELOCITY_H
#define SW_SYSTEMS_VELOCITY_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Velocity;
}

namespace spacewar {

class VelocitySystem final: public firefly::ISystem {
public:
	VelocitySystem(firefly::Engine* engine);
	~VelocitySystem() override;

	VelocitySystem(const VelocitySystem&) = delete;
	VelocitySystem& operator=(const VelocitySystem&) = delete;

private:
	void onUpdate() override;
	void processVelocity(firefly::Velocity* velocity) const;
};

}

#endif // SW_SYSTEMS_VELOCITY_H
