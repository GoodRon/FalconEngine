#include "PlayerControlSystem.h"

#include <SDL_timer.h>
#include <SDL_events.h>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/components/Player.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Position.h>
#include <firefly/components/State.h>
#include <firefly/components/Ammunition.h>
#include <firefly/components/Lifetime.h>

// TODO add only player with id

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

		addRequiredComponent(firefly::Player::ComponentName);
		addRequiredComponent(firefly::Position::ComponentName);
		addRequiredComponent(firefly::Velocity::ComponentName);
		addRequiredComponent(firefly::State::ComponentName);
		addRequiredComponent(firefly::Ammunition::ComponentName);
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

	void PlayerControlSystem::onUpdate() {
		processHold();
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

			if (_keyCodeAction == keyCode) {
				onActionPressed(true);
				return true;
			}

			if (keyCode == SDLK_ESCAPE) {
				getEngine()->stop();
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

			if (_keyCodeAction == keyCode) {
				onActionPressed(false);
				return true;
			}
			break;

		default:
			break;
		}
		return false;
	}

	firefly::Entity* PlayerControlSystem::findPlayer(int playerId) const {
		auto& entities = getEntities();
		for (auto& entity : entities) {
			auto playerComponent = entity.second->getComponent<firefly::Player>();

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

		auto component = playerEntity->getComponent<firefly::Velocity>();
		return component;
	}

	firefly::Position* PlayerControlSystem::getPosition(int playerId) const {
		firefly::Entity* playerEntity = findPlayer(playerId);
		if (!playerEntity) {
			return nullptr;
		}

		auto component = playerEntity->getComponent<firefly::Position>();
		return component;
	}

	firefly::State* PlayerControlSystem::getState(int playerId) const {
		firefly::Entity* playerEntity = findPlayer(playerId);
		if (!playerEntity) {
			return nullptr;
		}

		auto component = playerEntity->getComponent<firefly::State>();
		return component;
	}

	firefly::Ammunition* PlayerControlSystem::getAmmunition(int playerId) const {
		firefly::Entity* playerEntity = findPlayer(playerId);
		if (!playerEntity) {
			return nullptr;
		}

		auto component = playerEntity->getComponent<firefly::Ammunition>();
		return component;
	}

	void PlayerControlSystem::onUpPressed(bool isPressed) {
		_isUpPressed = isPressed;

		onUpHold();
	}

	void PlayerControlSystem::onLeftPressed(bool isPressed) {
		_isLeftPressed = isPressed;

		onLeftHold();
	}

	void PlayerControlSystem::onDownPressed(bool isPressed) {
		_isDownPressed = isPressed;

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
		stateComponent->timepoint = SDL_GetTicks64();
	}

	void PlayerControlSystem::onRightPressed(bool isPressed) {
		_isRightPressed = isPressed;

		onRightHold();
	}

	void PlayerControlSystem::onActionPressed(bool isPressed) {
		_isActionPressed = isPressed;

		if (!_isActionPressed) {
			return;
		} 

		shoot();
	}

	void PlayerControlSystem::processHold() {
		onUpHold();
		onLeftHold();
		onDownHold();
		onRightHold();
		onActionHold();
	}

	void PlayerControlSystem::onUpHold() {
		if (_isUpPressed) {
			setAcceleration(acceleration);
			return;
		} 

		setAcceleration(0.0);
	}

	void PlayerControlSystem::onLeftHold() {
		if (_isLeftPressed && _isRightPressed) {
			return;
		}

		if (_isLeftPressed) {
			rotate(-angleDelta * getElapsedMs() / 1000.0);
			return;	
		}

		if (_isRightPressed) {
			onRightHold();
			return;
		}
	}

	void PlayerControlSystem::onDownHold() {

	}

	void PlayerControlSystem::onRightHold() {
		if (_isLeftPressed && _isRightPressed) {
			return;
		}

		if (_isRightPressed) {
			rotate(angleDelta * getElapsedMs() / 1000.0);
			return;	
		}

		if (_isLeftPressed) {
			onLeftHold();
			return;
		}
	}

	void PlayerControlSystem::onActionHold() {
		
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

		const auto timepoint = SDL_GetTicks64();

		// TODO calc delta
		if (timepoint - weapon.lastShotTimepoint < 
			weapon.cooldownTimeMs) {
			return;
		}

		weapon.lastShotTimepoint = timepoint;

		auto entityPrototypes = getEngine()->getEntityPrototypes();
		auto entityManager = getEngine()->getEntityManager();

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
		lifetime->timepoint = timepoint;

		entityManager->addEntity(projectile);
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
