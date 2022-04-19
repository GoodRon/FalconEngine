#include "PlayerControlSystem.h"

#include <SDL_events.h>

#include <firefly/Entity.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/components/Player.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Position.h>

namespace spacewar {

	// TODO remove from here
	const int playerId = 1;
	const double speed = 90.0;
	const double acceleration = 15.0;
	const double angleDelta = 5.0;

	PlayerControlSystem::PlayerControlSystem(
		firefly::Engine* engine) :
		firefly::ISystem("PlayerControlSystem", engine),
		_keyCodeUp(SDLK_w),
		_keyCodeLeft(SDLK_a),
		_keyCodeDown(SDLK_s),
		_keyCodeRight(SDLK_d),
		_isUpPressed(false),
		_isLeftPressed(false),
		_isDownPressed(false),
		_isRightPressed(false) {

		_requiredComponents.push_front(firefly::Player::ComponentName);
		_requiredComponents.push_front(firefly::Position::ComponentName);
		_requiredComponents.push_front(firefly::Velocity::ComponentName);
	}

	PlayerControlSystem::~PlayerControlSystem() {
	}

	void PlayerControlSystem::setKeyCodes(int keyUp, int keyLeft, int keyDown, int keyRight) {
		_keyCodeUp = keyUp;
		_keyCodeLeft = keyLeft;
		_keyCodeDown = keyDown;
		_keyCodeRight = keyRight;

		onUpPressed(false);
		onLeftPressed(false);
		onDownPressed(false);
		onRightPressed(false);
	}

	bool PlayerControlSystem::onEvent(
		const std::shared_ptr<firefly::IEvent>& event) {
		if (!event) {
			return false;
		}

		if (event->getType() != firefly::EventType::NativeEvent) {
			return false;
		}

		auto nativeEvent = std::dynamic_pointer_cast<firefly::NativeEvent>(event);

		if (onPlayerInput(nativeEvent)) {
			return true;
		}

		return false;
	}

	bool PlayerControlSystem::onPlayerInput(
		const std::shared_ptr<firefly::NativeEvent>& event) {

		auto sdlEvent = event->getSDLEvent();
		int keyCode = 0;
		switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			keyCode = sdlEvent.key.keysym.sym;
			if (_keyCodeUp == keyCode) {
				onUpPressed(true);
				return true;
			}
			
			if (_keyCodeLeft == keyCode) {
				onLeftPressed(true);
				return true;
			}

			if (_keyCodeDown == keyCode) {
				onDownPressed(true);
				return true;
			}

			if (_keyCodeRight == keyCode) {
				onRightPressed(true);
				return true;
			}
			break;

		case SDL_KEYUP:
			keyCode = sdlEvent.key.keysym.sym;
			if (_keyCodeUp == keyCode) {
				onUpPressed(false);
				return true;
			}
			
			if (_keyCodeLeft == keyCode) {
				onLeftPressed(false);
				return true;
			}
			
			if (_keyCodeDown == keyCode) {
				onDownPressed(false);
				return true;
			}

			if (_keyCodeRight == keyCode) {
				onRightPressed(false);
				return true;
			}
			break;

		default:
			break;
		}
		return false;
	}

	firefly::Entity* PlayerControlSystem::findPlayer(int playerId) const {
		for (auto& entity : _entities) {
			auto playerComponent = static_cast<firefly::Player*>(
				entity.second->getComponent(
					firefly::getComponentId(firefly::Player::ComponentName)));

			if (playerComponent->playerId == playerId) {
				return entity.second;
			}
		}
		return nullptr;
	}

	firefly::Velocity* PlayerControlSystem::getVelocity(int playerId) const {
		firefly::Entity* playerEntity = findPlayer(playerId);
		if (!playerEntity) {
			return nullptr;
		}

		auto component = static_cast<firefly::Velocity*>(
			playerEntity->getComponent(
				firefly::getComponentId(firefly::Velocity::ComponentName)));
		return component;
	}

	firefly::Position* PlayerControlSystem::getPosition(int playerId) const {
		firefly::Entity* playerEntity = findPlayer(playerId);
		if (!playerEntity) {
			return nullptr;
		}

		auto component = static_cast<firefly::Position*>(
			playerEntity->getComponent(
				firefly::getComponentId(firefly::Position::ComponentName)));
		return component;
	}

	void PlayerControlSystem::onUpPressed(bool isPressed) {
		_isUpPressed = isPressed;

		if (_isUpPressed) {
			setAcceleration(acceleration);
			return;	
		}

		setAcceleration(0.0);
	}

	void PlayerControlSystem::onLeftPressed(bool isPressed) {
		_isLeftPressed = isPressed;

		if (_isLeftPressed && _isRightPressed) {
			return;
		}

		if (_isLeftPressed) {
			rotate(-angleDelta);
			return;	
		}

		if (_isRightPressed) {
			onRightPressed(true);
			return;
		}
	}

	void PlayerControlSystem::onDownPressed(bool isPressed) {
		_isDownPressed = isPressed;

	}

	void PlayerControlSystem::onRightPressed(bool isPressed) {
		_isRightPressed = isPressed;

		if (_isLeftPressed && _isRightPressed) {
			return;
		}

		if (_isRightPressed) {
			rotate(angleDelta);
			return;	
		}

		if (_isLeftPressed) {
			onLeftPressed(true);
			return;
		}
	}

	void PlayerControlSystem::setSpeedX(double speedX) {
		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->speedX = speedX;
	}

	void PlayerControlSystem::setSpeedY(double speedY) {
		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->speedY = speedY;
	}

	void PlayerControlSystem::setAcceleration(double acceleration) {
		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->acceleration = acceleration;
	}

	void PlayerControlSystem::rotate(double angle) {
		auto positionComponent = getPosition(playerId);
		if (!positionComponent) {
			return;
		}

		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->accelerationAngle += angle;
		/*
		if (velocityComponent->accelerationAngle > 360.0) {
			velocityComponent->accelerationAngle = 
				fmod(velocityComponent->accelerationAngle, 360.0);
		}*/

		positionComponent->angle += angle;
		/*
		if (positionComponent->angle > 360.0) {
			positionComponent->angle = 
				fmod(positionComponent->angle, 360.0);
		}
		*/
	}
}
