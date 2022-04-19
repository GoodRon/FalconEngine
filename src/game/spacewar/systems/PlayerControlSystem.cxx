#include "PlayerControlSystem.h"

#include <SDL_events.h>
#include <SDL_timer.h>

#include <firefly/Entity.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/components/Player.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Position.h>
#include <firefly/components/Visual.h>

namespace spacewar {

	// TODO remove from here
	const double speed = 90.0;
	const double acceleration = 15.0;
	const double angleDelta = 45.0;

	PlayerControlSystem::PlayerControlSystem(
		firefly::Engine* engine, int playerId, const std::string suffix) :
		firefly::ISystem("PlayerControlSystem" + suffix, engine),
		_playerId(playerId),
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

		_isUpPressed = false;
		_isLeftPressed = false;
		_isDownPressed = false;
		_isRightPressed = false;
	}

	void PlayerControlSystem::update() {
		const uint64_t timepoint = SDL_GetTicks64();
		const uint64_t elapsedMs = timepoint - _updateTimepoint;
		_updateTimepoint = timepoint;

		processPressed(elapsedMs);
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
				_isUpPressed = true;
				return true;
			}
			
			if (_keyCodeLeft == keyCode) {
				_isLeftPressed = true;
				return true;
			}

			if (_keyCodeDown == keyCode) {
				_isDownPressed = true;
				return true;
			}

			if (_keyCodeRight == keyCode) {
				_isRightPressed = true;
				return true;
			}
			break;

		case SDL_KEYUP:
			keyCode = sdlEvent.key.keysym.sym;
			if (_keyCodeUp == keyCode) {
				_isUpPressed = false;
				return true;
			}
			
			if (_keyCodeLeft == keyCode) {
				_isLeftPressed = false;
				return true;
			}
			
			if (_keyCodeDown == keyCode) {
				_isDownPressed = false;
				return true;
			}

			if (_keyCodeRight == keyCode) {
				_isRightPressed = false;
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

	firefly::Visual* PlayerControlSystem::getVisual(int playerId) const {
		firefly::Entity* playerEntity = findPlayer(playerId);
		if (!playerEntity) {
			return nullptr;
		}

		auto component = static_cast<firefly::Visual*>(
			playerEntity->getComponent(
				firefly::getComponentId(firefly::Visual::ComponentName)));
		return component;
	}

	void PlayerControlSystem::processPressed(uint64_t elapsedMs) {
		onUpPressed(elapsedMs);
		onLeftPressed(elapsedMs);
		onDownPressed(elapsedMs);
		onRightPressed(elapsedMs);
	}

	void PlayerControlSystem::onUpPressed(uint64_t elapsedMs) {
		// TODO move from here
		auto visualComponent = getVisual(_playerId);

		if (_isUpPressed) {
			setAcceleration(acceleration);

			if (visualComponent) {
				visualComponent->currentState = "Moving";
			}
			return;
		} 

		setAcceleration(0.0);
		
		if (visualComponent) {
			visualComponent->currentState = "Idle";
		}
	}

	void PlayerControlSystem::onLeftPressed(uint64_t elapsedMs) {
		if (_isLeftPressed && _isRightPressed) {
			return;
		}

		if (_isLeftPressed) {
			rotate(-angleDelta * elapsedMs / 1000.0);
			return;	
		}

		if (_isRightPressed) {
			onRightPressed(elapsedMs);
			return;
		}
	}

	void PlayerControlSystem::onDownPressed(uint64_t elapsedMs) {

	}

	void PlayerControlSystem::onRightPressed(uint64_t elapsedMs) {

		if (_isLeftPressed && _isRightPressed) {
			return;
		}

		if (_isRightPressed) {
			rotate(angleDelta * elapsedMs / 1000.0);
			return;	
		}

		if (_isLeftPressed) {
			onLeftPressed(elapsedMs);
			return;
		}
	}

	void PlayerControlSystem::setSpeedX(double speedX) {
		auto velocityComponent = getVelocity(_playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->speedX = speedX;
	}

	void PlayerControlSystem::setSpeedY(double speedY) {
		auto velocityComponent = getVelocity(_playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->speedY = speedY;
	}

	void PlayerControlSystem::setAcceleration(double acceleration) {
		auto velocityComponent = getVelocity(_playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->acceleration = acceleration;
	}

	void PlayerControlSystem::rotate(double angle) {
		auto positionComponent = getPosition(_playerId);
		if (!positionComponent) {
			return;
		}

		auto velocityComponent = getVelocity(_playerId);
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
