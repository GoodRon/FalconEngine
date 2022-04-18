/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_PLAYER_CONTROL_H
#define SW_SYSTEMS_PLAYER_CONTROL_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Entity;
	class NativeEvent;
}

namespace spacewar {

class PlayerControlSystem: public firefly::ISystem {
public:
	PlayerControlSystem(firefly::Engine* engine);
	~PlayerControlSystem() override;

	PlayerControlSystem(const PlayerControlSystem&) = delete;
	PlayerControlSystem& operator=(const PlayerControlSystem&) = delete;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) const override;

private:
	bool onPlayerOneInput(
		const std::shared_ptr<firefly::NativeEvent>& event) const;
	bool onPlayerTwoInput(
		const std::shared_ptr<firefly::NativeEvent>& event) const;

	firefly::Entity* findPlayer(int playerId) const;

	void setAccelerationX(
		int playerId, int accelerationX) const;

	void setAccelerationY(
		int playerId, int accelerationY) const;
};

}

#endif // SW_SYSTEMS_PLAYER_CONTROL_H
