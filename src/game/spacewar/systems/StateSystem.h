/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_SHIP_STATE_H
#define SW_SYSTEMS_SHIP_STATE_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Entity;
	class IEvent;
}

namespace spacewar {

class StateSystem final: public firefly::ISystem {
public:
	StateSystem(firefly::Engine* engine);
	~StateSystem() override;

	StateSystem(const StateSystem&) = delete;
	StateSystem& operator=(const StateSystem&) = delete;

private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;
	void onUpdate() override;

	void updateState(
		firefly::Entity* entity) const;
	void switchState(
		firefly::Entity* entity, int state) const;

	void updateIdle(firefly::Entity* entity) const;
	void updateMoving(firefly::Entity* entity) const;
	void updateHyperspace(firefly::Entity* entity) const;
	void updateDestroyed(firefly::Entity* entity) const;
};

}

#endif // SW_SYSTEMS_SHIP_STATE_H
