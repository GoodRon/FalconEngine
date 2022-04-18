/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_PLAYER_CONTROL_H
#define SW_SYSTEMS_PLAYER_CONTROL_H

#include "falcon/systems/ISystem.h"

namespace spacewar {

class PlayerControlSystem: public falcon::ISystem {
public:
	PlayerControlSystem(falcon::Engine* engine);
	~PlayerControlSystem() override;

	PlayerControlSystem(const PlayerControlSystem&) = delete;
	PlayerControlSystem& operator=(const PlayerControlSystem&) = delete;

	bool onEvent(
		const std::shared_ptr<falcon::IEvent>& event) const override;

private:
	bool checkComponents(falcon::Entity* entity) const override;
};

}

#endif // SW_SYSTEMS_PLAYER_CONTROL_H
