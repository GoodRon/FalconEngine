/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_PLAYER_CONTROL_H
#define SW_SYSTEMS_PLAYER_CONTROL_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Entity;
	class Velocity;
	class Position;
	class NativeEvent;
}

namespace spacewar {

class PlayerControlSystem: public firefly::ISystem {
public:
	PlayerControlSystem(firefly::Engine* engine);
	~PlayerControlSystem() override;

	PlayerControlSystem(const PlayerControlSystem&) = delete;
	PlayerControlSystem& operator=(const PlayerControlSystem&) = delete;

	void setKeyCodes(int keyUp, int keyLeft, int keyDown, int keyRight);

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	bool onPlayerInput(
		const std::shared_ptr<firefly::NativeEvent>& event);

	firefly::Entity* findPlayer(int playerId) const;

	firefly::Velocity* getVelocity(int playerId) const;
	firefly::Position* getPosition(int playerId) const;

	void onUpPressed(bool isPressed);
	void onLeftPressed(bool isPressed);
	void onDownPressed(bool isPressed);
	void onRightPressed(bool isPressed);

	void setSpeedX(double speedX);
	void setSpeedY(double speedY);

	void setAcceleration(double acceleration);
	void rotate(double angle);

private:
	int _keyCodeUp;
	int _keyCodeLeft;
	int _keyCodeDown;
	int _keyCodeRight;
	bool _isUpPressed;
	bool _isLeftPressed;
	bool _isDownPressed;
	bool _isRightPressed;
};

}

#endif // SW_SYSTEMS_PLAYER_CONTROL_H
