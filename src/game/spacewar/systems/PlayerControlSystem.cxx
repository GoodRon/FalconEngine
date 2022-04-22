#include "PlayerControlSystem.h"

#include <random>

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

#include "StateNames.h"
#include "misc/VelocityHelpers.h"

namespace spacewar {

	static int randomInt(int min, int max) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

	// TODO move to config here
	const double acceleration = 20.0;
	const double angleDelta = 45.0;

	PlayerControlSystem::PlayerControlSystem(
		firefly::Engine* engine, int playerId, 
		const std::string playerName) :
		firefly::ISystem("PlayerControlSystem_" + playerName, engine),
		_playerId(playerId),
		_keyCodeUp(SDLK_w),
		_keyCodeLeft(SDLK_a),
		_keyCodeDown(SDLK_s),
		_keyCodeRight(SDLK_d),
		_isUpPressed(false),
		_isLeftPressed(false),
		_isDownPressed(false),
		_isRightPressed(false),
		_player(nullptr) {

		addRequiredComponent(firefly::Player::ComponentName);
		addRequiredComponent(firefly::Position::ComponentName);
		addRequiredComponent(firefly::Velocity::ComponentName);
		addRequiredComponent(firefly::State::ComponentName);
		addRequiredComponent(firefly::Ammunition::ComponentName);
	}

	PlayerControlSystem::~PlayerControlSystem() {
	}

	void PlayerControlSystem::setKeyCodes(int keyUp, int keyLeft, 
		int keyDown, int keyRight) {
		_keyCodeUp = keyUp;
		_keyCodeLeft = keyLeft;
		_keyCodeDown = keyDown;
		_keyCodeRight = keyRight;

		_isUpPressed = false;
		_isLeftPressed = false;
		_isDownPressed = false;
		_isRightPressed = false;
	}

	void PlayerControlSystem::onUpdate() {
		onUpHold();
		onLeftHold();
		onDownHold();
		onRightHold();
	}

	bool PlayerControlSystem::onEvent(
		const std::shared_ptr<firefly::IEvent>& event) {
		if (!event) {
			return false;
		}

		if (event->getType() != firefly::EventType::Native) {
			return false;
		}

		auto nativeEvent = std::dynamic_pointer_cast<firefly::NativeEvent>(event);

		auto sdlEvent = nativeEvent->getSDLEvent();
		if (sdlEvent.type && sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
			// NOTE exit game
			getEngine()->stop();
			return true;
		}

		if (onPlayerInput(nativeEvent)) {
			return true;
		}
		return false;
	}

	bool PlayerControlSystem::onRegisterEntity(firefly::Entity* entity) {
		if (!entity) {
			return false;
		}

		auto playerComponent = entity->getComponent<firefly::Player>();
		if (playerComponent->playerId != _playerId) {
			return false;
		}
		_player = entity;
		return true;
	}

	void PlayerControlSystem::onUnregisterEntity(firefly::Entity* entity) {
		if (_player != entity) {
			return;
		}
		_player = nullptr;
	}

	bool PlayerControlSystem::onPlayerInput(
		const std::shared_ptr<firefly::NativeEvent>& event) {

		if (!_player) {
			return false;
		}

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

		onDownHold();
	}

	void PlayerControlSystem::onRightPressed(bool isPressed) {
		_isRightPressed = isPressed;

		onRightHold();
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
			hyperspace();
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
		if (!_isDownPressed) {
			return;
		}

		const auto stateComponent =
			_player->getComponent<firefly::State>();
		if (stateComponent->current == stateNameDestroyed()) {
			return;
		}

		shoot();
	}

	void PlayerControlSystem::onRightHold() {
		if (_isLeftPressed && _isRightPressed) {
			hyperspace();
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

	void PlayerControlSystem::setAcceleration(double acceleration) const {
		if (!_player) {
			return;
		}

		const auto velocityComponent = _player->getComponent<firefly::Velocity>();
		velocityComponent->acceleration = acceleration;
	}

	void PlayerControlSystem::shoot() const {
		if (!_player) {
			return;
		}

		const auto stateComponent = 
			_player->getComponent<firefly::State>();
		if (stateComponent->current == stateNameDestroyed() ||
			stateComponent->current == stateNameHyperspace()) {
			return;
		}

		const auto ammunitionComponent = 
			_player->getComponent<firefly::Ammunition>();

		// TODO improve
		const std::string weaponName("RocketLauncher");

		if (ammunitionComponent->weapons.find(weaponName) == 
			ammunitionComponent->weapons.end()) {
			return;
		}

		auto& weapon = ammunitionComponent->weapons[weaponName];

		const auto timepoint = SDL_GetTicks64();
		const auto elapsedMs = timepoint - weapon.lastShotTimepoint;
		if (elapsedMs < weapon.cooldownTimeMs) {
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

		const auto playerPosition = _player->getComponent<firefly::Position>();

		velocity->speedDirection = playerPosition->direction;
		position->direction = playerPosition->direction;
		position->x = playerPosition->x;
		position->y = playerPosition->y;
		lifetime->timepoint = timepoint;

		move(position, 36, playerPosition->direction);

		entityManager->addEntity(projectile);
	}

	void PlayerControlSystem::hyperspace() const {
		if (!_player) {
			return;
		}

		const auto stateComponent = 
			_player->getComponent<firefly::State>();

		if (stateComponent->current == stateNameDestroyed() ||
			stateComponent->current == stateNameHyperspace()) {
			return;
		}

		constexpr int chanceOfMulfunction = 5;
		if (randomInt(0, 100) <= chanceOfMulfunction) {
			stateComponent->current = stateNameDestroyed();
			return;
		}

		const std::string nextState = stateNameHyperspace();

		if (stateComponent->current == nextState) {
			return;
		}

		stateComponent->previous = stateComponent->current;
		stateComponent->current = nextState;
		stateComponent->timepoint = SDL_GetTicks64();
	}

	void PlayerControlSystem::rotate(double angle) const {
		if (!_player) {
			return;
		}

		const auto positionComponent = 
			_player->getComponent<firefly::Position>();
		const auto velocityComponent = 
			_player->getComponent<firefly::Velocity>();

		velocityComponent->accelerationDirection =
			normalizeAngle(velocityComponent->accelerationDirection + angle);

		positionComponent->direction =
			normalizeAngle(positionComponent->direction + angle);
	}
}
