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
	class NativeEvent;
}

namespace spacewar {

class PlayerControlSystem: public firefly::ISystem {
public:
	// TODO remove suffix, make unique name
	PlayerControlSystem(firefly::Engine* engine, int playerId, 
		const std::string suffix);
	~PlayerControlSystem() override;

	PlayerControlSystem(const PlayerControlSystem&) = delete;
	PlayerControlSystem& operator=(const PlayerControlSystem&) = delete;

	void setKeyCodes(int keyUp, int keyLeft, int keyDown, int keyRight);

	void update() override;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	bool onPlayerInput(
		const std::shared_ptr<firefly::NativeEvent>& event);

	firefly::Entity* findPlayer(int playerId) const;

	firefly::Velocity* getVelocity(int playerId) const;
	firefly::Position* getPosition(int playerId) const;
	firefly::State* getState(int playerId) const;

	void processPressed(uint64_t elapsedMs);
	void onUpPressed(uint64_t elapsedMs);
	void onLeftPressed(uint64_t elapsedMs);
	void onDownPressed(uint64_t elapsedMs);
	void onRightPressed(uint64_t elapsedMs);

	void setSpeedX(double speedX);
	void setSpeedY(double speedY);

	void setAcceleration(double acceleration);
	void rotate(double angle);

private:
	const int _playerId;
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
