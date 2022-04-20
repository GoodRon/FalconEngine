#include "PlayerControlSystem.h"

#include <SDL_events.h>
#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/GameObject.h>
#include <firefly/ObjectManager.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/components/Player.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Position.h>
#include <firefly/components/State.h>
#include <firefly/components/Ammunition.h>
#include <firefly/components/Lifetime.h>

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
		_keyCodeAction(SDLK_SPACE),
		_isUpPressed(false),
		_isLeftPressed(false),
		_isDownPressed(false),
		_isRightPressed(false),
		_isActionPressed(false) {

		_requiredComponents.push_front(firefly::Player::ComponentName);
		_requiredComponents.push_front(firefly::Position::ComponentName);
		_requiredComponents.push_front(firefly::Velocity::ComponentName);
		_requiredComponents.push_front(firefly::State::ComponentName);
		_requiredComponents.push_front(firefly::Ammunition::ComponentName);
	}

	PlayerControlSystem::~PlayerControlSystem() {
	}

	void PlayerControlSystem::setKeyCodes(int keyUp, int keyLeft, 
		int keyDown, int keyRight, int keyAction) {
		_keyCodeUp = keyUp;
		_keyCodeLeft = keyLeft;
		_keyCodeDown = keyDown;
		_keyCodeRight = keyRight;
		_keyCodeAction = keyAction;

		_isUpPressed = false;
		_isLeftPressed = false;
		_isDownPressed = false;
		_isRightPressed = false;
		_isActionPressed = false;
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

			if (_keyCodeAction == keyCode) {
				_isActionPressed = true;
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

			if (_keyCodeAction == keyCode) {
				_isActionPressed = false;
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


	// TODO pass the entity ptr
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

	firefly::State* PlayerControlSystem::getState(int playerId) const {
		firefly::Entity* playerEntity = findPlayer(playerId);
		if (!playerEntity) {
			return nullptr;
		}

		auto component = static_cast<firefly::State*>(
			playerEntity->getComponent(
				firefly::getComponentId(firefly::State::ComponentName)));
		return component;
	}

	firefly::Ammunition* PlayerControlSystem::getAmmunition(int playerId) const {
		firefly::Entity* playerEntity = findPlayer(playerId);
		if (!playerEntity) {
			return nullptr;
		}

		auto component = static_cast<firefly::Ammunition*>(
			playerEntity->getComponent(
				firefly::getComponentId(firefly::Ammunition::ComponentName)));
		return component;
	}

	void PlayerControlSystem::processPressed(uint64_t elapsedMs) {
		onUpPressed(elapsedMs);
		onLeftPressed(elapsedMs);
		onDownPressed(elapsedMs);
		onRightPressed(elapsedMs);
		onActionPressed(elapsedMs);
	}

	void PlayerControlSystem::onUpPressed(uint64_t elapsedMs) {
		if (_isUpPressed) {
			setAcceleration(acceleration);
			return;
		} 

		setAcceleration(0.0);
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
		// TODO improve
		auto stateComponent = getState(_playerId);
		if (!stateComponent) {
			return;
		}

		if (!_isDownPressed) {
			return;
		}

		const std::string nextState = "Hyperspace";

		if (stateComponent->current == nextState) {
			return;
		}

		stateComponent->previous = stateComponent->current;
		stateComponent->current = nextState;
		stateComponent->timepoint = _updateTimepoint;
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

	// TODO pressed and hold
	void PlayerControlSystem::onActionPressed(uint64_t elapsedMs) {
		if (!_isActionPressed) {
			return;
		} 

		shoot();
	}

	void PlayerControlSystem::setAcceleration(double acceleration) const {
		auto velocityComponent = getVelocity(_playerId);
		if (!velocityComponent) {
			return;
		}

		velocityComponent->acceleration = acceleration;
	}

	void PlayerControlSystem::shoot() const {
		auto ammunitionComponent = getAmmunition(_playerId);
		if (!ammunitionComponent) {
			return;
		}

		// TODO improve
		const std::string weaponName("RocketLauncher");

		if (ammunitionComponent->weapons.find(weaponName) == 
			ammunitionComponent->weapons.end()) {
			return;
		}

		auto& weapon = ammunitionComponent->weapons[weaponName];

		// TODO calc delta
		if (_updateTimepoint - weapon.lastShotTimepoint < 
			weapon.cooldownTimeMs) {
			return;
		}

		weapon.lastShotTimepoint = _updateTimepoint;

		auto entityPrototypes = _engine->getEntityPrototypes();
		auto objectManager = _engine->getObjectManager();

		auto projectile = entityPrototypes->makeEntity(weapon.projectile);
		if (!projectile) {
			return;
		}

		auto velocity = projectile->getComponent<firefly::Velocity>();
		auto position = projectile->getComponent<firefly::Position>();
		auto lifetime = projectile->getComponent<firefly::Lifetime>();
		if (!velocity || !position || !lifetime) {
			return;
		}

		auto playerPosition = getPosition(_playerId);
		if (!playerPosition) {
			return;
		}

		velocity->speedAngle = playerPosition->angle;
		position->angle = playerPosition->angle;
		position->x = playerPosition->x + 30.0;
		position->y = playerPosition->y + 30.0;
		lifetime->timepoint = _updateTimepoint;

		std::shared_ptr<firefly::GameObject> object(new firefly::GameObject(projectile));
		objectManager->registerObject(object);
	}

	void PlayerControlSystem::rotate(double angle) const {
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
