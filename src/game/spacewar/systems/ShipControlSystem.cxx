#include "ShipControlSystem.h"

#include <random>

#include <SDL_timer.h>
#include <SDL_events.h>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/EventManager.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/events/StateEvent.h>
#include <firefly/components/Player.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Position.h>
#include <firefly/components/State.h>
#include <firefly/components/Ammunition.h>
#include <firefly/components/Lifetime.h>
#include <firefly/components/ShipControls.h>

#include "ObjectStates.h"
#include "misc/VelocityHelpers.h"

namespace spacewar {

	static int randomInt(int min, int max) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

	// TODO move to config here
	constexpr double acceleration = 3.0;
	constexpr double angleDelta = 30.0;

	ShipControlSystem::ShipControlSystem(
		firefly::Engine* engine):
		firefly::ISystem(ShipControlSystem::Name, engine) {

		addRequiredComponent(firefly::Player::ComponentName);
		addRequiredComponent(firefly::ShipControls::ComponentName);
		addRequiredComponent(firefly::Position::ComponentName);
		addRequiredComponent(firefly::Velocity::ComponentName);
		addRequiredComponent(firefly::State::ComponentName);
		addRequiredComponent(firefly::Ammunition::ComponentName);
	}

	ShipControlSystem::~ShipControlSystem() {
	}

	void ShipControlSystem::onUpdate() {
		for (auto& entity: getEntities()) {
			if (!entity.second->isActive()) {
				continue;
			}

			const auto controls = entity.second->
				getComponent<firefly::ShipControls>();
			if (!controls) {
				continue;
			}

			onUpPressed(entity.second, 
				controls, controls->isUpPressed);
			onDownPressed(entity.second, 
				controls, controls->isDownPressed);
			onLeftPressed(entity.second, 
				controls, controls->isLeftPressed);
			onRightPressed(entity.second, 
				controls, controls->isRightPressed);
		}
	}

	bool ShipControlSystem::onEvent(
		const std::shared_ptr<firefly::IEvent>& event) {
		if (!event) {
			return false;
		}

		if (event->getType() != firefly::EventType::Native) {
			return false;
		}

		const auto nativeEvent = 
			static_cast<firefly::NativeEvent*>(event.get());
		
		for (auto& entity: getEntities()) {
			if (!entity.second->isActive()) {
				continue;
			}

			if (onPlayerInput(entity.second, nativeEvent)) {
				return true;
			}
		}
		return false;
	}

	bool ShipControlSystem::onPlayerInput(
		firefly::Entity* entity,
		firefly::NativeEvent* event) const {

		if (!entity || !event) {
			return false;
		}

		const auto controls = entity->getComponent<firefly::ShipControls>();
		if (!controls) {
			return false;
		}
		
		auto sdlEvent = event->getSDLEvent();
		int keyCode = 0;
		switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			keyCode = sdlEvent.key.keysym.sym;
			if (controls->keyCodeUp == keyCode) {
				onUpPressed(entity, controls, true);
				return true;
			}
			
			if (controls->keyCodeLeft == keyCode) {
				onLeftPressed(entity, controls, true);
				return true;
			}

			if (controls->keyCodeDown == keyCode) {
				onDownPressed(entity, controls, true);
				return true;
			}

			if (controls->keyCodeRight == keyCode) {
				onRightPressed(entity, controls, true);
				return true;
			}
			break;

		case SDL_KEYUP:
			keyCode = sdlEvent.key.keysym.sym;
			if (controls->keyCodeUp == keyCode) {
				onUpPressed(entity, controls, false);
				return true;
			}
			
			if (controls->keyCodeLeft == keyCode) {
				onLeftPressed(entity, controls, false);
				return true;
			}
			
			if (controls->keyCodeDown == keyCode) {
				onDownPressed(entity, controls, false);
				return true;
			}

			if (controls->keyCodeRight == keyCode) {
				onRightPressed(entity, controls, false);
				return true;
			}
			break;

		default:
			break;
		}
		return false;
	}

	void ShipControlSystem::onUpPressed(
		firefly::Entity* entity, 
		firefly::ShipControls* controls, 
		bool isPressed) const {

		controls->isUpPressed = isPressed;

		if (controls->isUpPressed) {
			setAcceleration(entity, acceleration);
			return;
		} 
		setAcceleration(entity, 0.0);
	}

	void ShipControlSystem::onDownPressed(
		firefly::Entity* entity, 
		firefly::ShipControls* controls, 
		bool isPressed) const {

		controls->isDownPressed = isPressed;

		if (!controls->isDownPressed) {
			return;
		}

		const auto stateComponent =
			entity->getComponent<firefly::State>();

		if (stateComponent->current != ObjectState::Idle &&
			stateComponent->current != ObjectState::Moving) {
			return;
		}

		shoot(entity);
	}

	void ShipControlSystem::onLeftPressed(
		firefly::Entity* entity, 
		firefly::ShipControls* controls, 
		bool isPressed) const {

		controls->isLeftPressed = isPressed;

		if (controls->isLeftPressed && controls->isRightPressed) {
			hyperspace(entity);
			return;
		}

		if (controls->isLeftPressed) {
			rotate(entity, -angleDelta * getElapsedMs() / 1000.0);
			return;	
		}

		if (controls->isRightPressed) {
			onRightPressed(entity, controls, controls->isRightPressed);
			return;
		}
	}

	void ShipControlSystem::onRightPressed(
		firefly::Entity* entity, 
		firefly::ShipControls* controls, 
		bool isPressed) const {

		controls->isRightPressed = isPressed;

		if (controls->isLeftPressed && controls->isRightPressed) {
			hyperspace(entity);
			return;
		}

		if (controls->isRightPressed) {
			rotate(entity, angleDelta * getElapsedMs() / 1000.0);
			return;	
		}

		if (controls->isLeftPressed) {
			onLeftPressed(entity, controls, controls->isLeftPressed);
			return;
		}
	}

	void ShipControlSystem::setAcceleration(
		firefly::Entity* entity,
		double acceleration) const {

		const auto positionComponent = 
			entity->getComponent<firefly::Position>();
		const auto velocityComponent = 
			entity->getComponent<firefly::Velocity>();

		velocityComponent->acceleration = acceleration;
		velocityComponent->accelerationDirection 
			= positionComponent->direction;
	}

	void ShipControlSystem::rotate(
		firefly::Entity* entity, 
		double angle) const {

		const auto positionComponent = 
			entity->getComponent<firefly::Position>();

		positionComponent->direction =
			normalizeAngle(positionComponent->direction + angle);
	}

	// TODO make a weapon system
	void ShipControlSystem::shoot(firefly::Entity* entity) const {
		const auto stateComponent = 
			entity->getComponent<firefly::State>();

		if (stateComponent->current != ObjectState::Idle &&
			stateComponent->current != ObjectState::Moving) {
			return;
		}

		const auto ammunitionComponent = 
			entity->getComponent<firefly::Ammunition>();

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

		projectile->setActive(true);

		auto velocity = projectile->getComponent<firefly::Velocity>();
		auto position = projectile->getComponent<firefly::Position>();
		auto lifetime = projectile->getComponent<firefly::Lifetime>();
		if (!velocity || !position || !lifetime) {
			return;
		}

		const auto playerPosition = entity->getComponent<firefly::Position>();

		velocity->speedDirection = playerPosition->direction;
		position->direction = playerPosition->direction;
		position->x = playerPosition->x;
		position->y = playerPosition->y;
		lifetime->timepoint = timepoint;

		move(position, 36, playerPosition->direction);

		entityManager->addEntity(projectile);
	}

	void ShipControlSystem::hyperspace(firefly::Entity* entity) const {
		const auto eventManager = getEngine()->getEventManager();

		const auto stateComponent = 
			entity->getComponent<firefly::State>();

		if (stateComponent->current != ObjectState::Idle &&
			stateComponent->current != ObjectState::Moving) {
			return;
		}

		ObjectState nextState = ObjectState::Hyperspace;

		constexpr int chanceOfMulfunction = 5;
		if (randomInt(0, 100) <= chanceOfMulfunction) {
			nextState = ObjectState::Exploading;
		}

		std::shared_ptr<firefly::IEvent> event(new firefly::StateEvent(
			entity->getId(), nextState));
					
		eventManager->registerEvent(std::move(event));
	}
}
