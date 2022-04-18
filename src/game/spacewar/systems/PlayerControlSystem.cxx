#include "PlayerControlSystem.h"

#include <SDL_events.h>

#include <firefly/Entity.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/components/Player.h>
#include <firefly/components/Velocity.h>

namespace spacewar {

	// TODO remove from here
	const int playerId = 1;
	const double speedX = 90.0;
	const double speedY = 90.0;
	const double accelerationX = 15.0;
	const double accelerationY = 15.0;

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

		auto velocityComponent = static_cast<firefly::Velocity*>(
			playerEntity->getComponent(
				firefly::getComponentId(firefly::Velocity::ComponentName)));
		return velocityComponent;
	}

	void PlayerControlSystem::onUpPressed(bool isPressed) {
		_isUpPressed = isPressed;

		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return;
		}

		if (_isDownPressed && _isUpPressed) {
			setAccelerationY(0.0);
			return;
		}

		if (_isUpPressed) {
			setAccelerationY(-accelerationY);
			return;	
		}

		if (_isDownPressed) {
			onDownPressed(true);
			return;
		}

		setAccelerationY(0.0);
	}

	void PlayerControlSystem::onLeftPressed(bool isPressed) {
		_isLeftPressed = isPressed;

		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return;
		}

		if (_isLeftPressed && _isRightPressed) {
			setAccelerationX(0.0);
			return;
		}

		if (_isLeftPressed) {
			setAccelerationX(-accelerationX);
			return;	
		}

		if (_isRightPressed) {
			onRightPressed(true);
			return;
		}

		setAccelerationX(0.0);
	}

	void PlayerControlSystem::onDownPressed(bool isPressed) {
		_isDownPressed = isPressed;

		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return;
		}

		if (_isDownPressed && _isUpPressed) {
			setAccelerationY(0.0);
			return;
		}

		if (_isDownPressed) {
			setAccelerationY(accelerationY);
			return;	
		}

		if (_isUpPressed) {
			setAccelerationY(true);
			return;
		}

		setAccelerationY(0.0);
	}

	void PlayerControlSystem::onRightPressed(bool isPressed) {
		_isRightPressed = isPressed;

		if (_isLeftPressed && _isRightPressed) {
			setAccelerationX(0.0);
			return;
		}

		if (_isRightPressed) {
			setAccelerationX(accelerationX);
			return;	
		}

		if (_isLeftPressed) {
			onLeftPressed(true);
			return;
		}

		setAccelerationX(0.0);
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

	void PlayerControlSystem::setAccelerationX(double accelerationX) {
		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->accelerationX = accelerationX;
	}

	void PlayerControlSystem::setAccelerationY(double accelerationY) {
		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->accelerationY = accelerationY;
	}
}