/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_SHIP_STATE_H
#define SW_SYSTEMS_SHIP_STATE_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Entity;
}

namespace spacewar {

class ShipStateSystem final: public firefly::ISystem {
public:
	ShipStateSystem(firefly::Engine* engine);
	~ShipStateSystem() override;

	ShipStateSystem(const ShipStateSystem&) = delete;
	ShipStateSystem& operator=(const ShipStateSystem&) = delete;

private:
	void onUpdate() override;

	void updateState(
		firefly::Entity* entity) const;

	void updateIdle(firefly::Entity* entity) const;
	void updateMoving(firefly::Entity* entity) const;
	void updateHyperspace(firefly::Entity* entity) const;
	void updateDestroyed(firefly::Entity* entity) const;
};

}

#endif // SW_SYSTEMS_SHIP_STATE_H
