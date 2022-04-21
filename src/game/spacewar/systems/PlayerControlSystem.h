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
	class State;
	class Ammunition;
	class NativeEvent;
}

namespace spacewar {

class PlayerControlSystem final: public firefly::ISystem {
public:
	PlayerControlSystem(firefly::Engine* engine, int playerId, 
		const std::string playerName);
	~PlayerControlSystem() override;

	PlayerControlSystem(const PlayerControlSystem&) = delete;
	PlayerControlSystem& operator=(const PlayerControlSystem&) = delete;

	void setKeyCodes(int keyUp, int keyLeft, int keyDown, 
		int keyRight, int keyAction);

	void onUpdate() override;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	bool onRegisterEntity(firefly::Entity* entity) override;
	void onUnregisterEntity(firefly::Entity* entity) override;

	bool onPlayerInput(
		const std::shared_ptr<firefly::NativeEvent>& event);

	void onUpPressed(bool isPressed);
	void onLeftPressed(bool isPressed);
	void onDownPressed(bool isPressed);
	void onRightPressed(bool isPressed);
	void onActionPressed(bool isPressed);

	void onUpHold();
	void onLeftHold();
	void onDownHold();
	void onRightHold();
	void onActionHold();

	void setAcceleration(double acceleration) const;
	void rotate(double angle) const;
	void shoot() const;

private:
	const int _playerId;
	int _keyCodeUp;
	int _keyCodeLeft;
	int _keyCodeDown;
	int _keyCodeRight;
	int _keyCodeAction;
	bool _isUpPressed;
	bool _isLeftPressed;
	bool _isDownPressed;
	bool _isRightPressed;
	bool _isActionPressed;
	firefly::Entity* _player;
};

}

#endif // SW_SYSTEMS_PLAYER_CONTROL_H
