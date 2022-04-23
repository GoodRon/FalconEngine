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
	inline static const std::string Name = "VelocitySystem";
	
	VelocitySystem(firefly::Engine* engine);
	~VelocitySystem() override;

	VelocitySystem(const VelocitySystem&) = delete;
	VelocitySystem& operator=(const VelocitySystem&) = delete;

private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;
	void onUpdate() override;
	void processVelocity(firefly::Velocity* velocity) const;

	void updateSpeed(firefly::EntityID id, 
		double speed, double direction) const;
	void accelerateEntity(firefly::EntityID id, 
		double acceleration, double direction) const;
};

}

#endif // SW_SYSTEMS_VELOCITY_H
