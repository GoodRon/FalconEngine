#include "ShipControlSystem.h"

#include <SDL_timer.h>
#include <SDL_events.h>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/EventManager.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/events/StateEvent.h>
#include <firefly/events/AddAccelerationEvent.h>
#include <firefly/events/SetAccelerationEvent.h>
#include <firefly/events/AddSpeedEvent.h>
#include <firefly/events/SetSpeedEvent.h>
#include <firefly/events/PositionEvent.h>
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

	// TODO move to config here
	constexpr double acceleration = 3.0;
	constexpr double angleDelta = 40.0;

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

		const auto eventManager = getEngine()->getEventManager();
		const auto stateComponent = 
			entity->getComponent<firefly::State>();

		if (!controls->isUpPressed) {
			// TODO make a swichState func
			if (stateComponent->current != ObjectState::Moving) {
				return;
			}

			std::shared_ptr<firefly::IEvent> event(new firefly::StateEvent(
				entity->getId(), ObjectState::Idle));
						
			eventManager->registerEvent(std::move(event));
			return;
		} 

		const auto positionComponent = 
			entity->getComponent<firefly::Position>();

		addAcceleration(
			entity, acceleration, positionComponent->direction);

		if (stateComponent->current != ObjectState::Idle) {
			return;
		}

		std::shared_ptr<firefly::IEvent> event(new firefly::StateEvent(
				entity->getId(), ObjectState::Moving));
						
		eventManager->registerEvent(std::move(event));
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
		double acceleration, double direction, bool isConstantAcceleration) const {

		std::shared_ptr<firefly::IEvent> event(
			new firefly::SetAccelerationEvent(
				entity->getId(), acceleration, direction, isConstantAcceleration));
			
		const auto eventManager = getEngine()->getEventManager();		
		eventManager->registerEvent(std::move(event));
	}

	void ShipControlSystem::addAcceleration(
		firefly::Entity* entity,
		double acceleration, double direction) const {

		std::shared_ptr<firefly::IEvent> event(
			new firefly::AddAccelerationEvent(
				entity->getId(), acceleration, direction));
		
		const auto eventManager = getEngine()->getEventManager();			
		eventManager->registerEvent(std::move(event));
	}

	void ShipControlSystem::addSpeed(firefly::Entity* entity,
		double speed, double direction) const {

		std::shared_ptr<firefly::IEvent> event(
			new firefly::AddSpeedEvent(
				entity->getId(), speed, direction));
					
		const auto eventManager = getEngine()->getEventManager();
		eventManager->registerEvent(std::move(event));
	}

	void ShipControlSystem::setSpeed(firefly::Entity* entity,
		double speed, double direction) const {

		std::shared_ptr<firefly::IEvent> event(
			new firefly::SetSpeedEvent(
				entity->getId(), speed, direction));
		
		const auto eventManager = getEngine()->getEventManager();
		eventManager->registerEvent(std::move(event));
	}

	void ShipControlSystem::setPosition(firefly::Entity* entity,
		double x, double y, double direction) const {

		std::shared_ptr<firefly::IEvent> event(
			new firefly::PositionEvent(
				entity->getId(), x, y, direction));
					
		const auto eventManager = getEngine()->getEventManager();
		eventManager->registerEvent(std::move(event));
	}

	void ShipControlSystem::rotate(
		firefly::Entity* entity, 
		double angle) const {

		const auto positionComponent = 
			entity->getComponent<firefly::Position>();

		std::shared_ptr<firefly::IEvent> event(
			new firefly::PositionEvent(
				entity->getId(), positionComponent->x, positionComponent->y,
				normalizeAngle(positionComponent->direction + angle)));

		const auto eventManager = getEngine()->getEventManager();
		eventManager->registerEvent(std::move(event));
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

		auto velocity = projectile->getComponent<firefly::Velocity>();
		auto position = projectile->getComponent<firefly::Position>();
		auto lifetime = projectile->getComponent<firefly::Lifetime>();
		if (!velocity || !position || !lifetime) {
			return;
		}

		projectile->setActive(true);
		entityManager->addEntity(projectile);

		const auto playerPosition = entity->getComponent<firefly::Position>();
		const auto playerVelocity = entity->getComponent<firefly::Velocity>();

		// TODO improve
		constexpr double spawnDistance = 27.0;
		double x = playerPosition->x;
		double y = playerPosition->y;
		movePoint(x, y, spawnDistance, 
			playerPosition->direction);

		setSpeed(projectile.get(), velocity->speed, 
			playerPosition->direction);
		addSpeed(projectile.get(), playerVelocity->speed, 
			playerVelocity->speedDirection);
		setAcceleration(projectile.get(), velocity->acceleration, 
			playerPosition->direction, velocity->isConstantAcceleration);
		setPosition(projectile.get(), x, y, playerPosition->direction);

		// TODO send event
		lifetime->timepoint = timepoint;
	}

	void ShipControlSystem::hyperspace(firefly::Entity* entity) const {

		const auto stateComponent = 
			entity->getComponent<firefly::State>();

		if (stateComponent->current != ObjectState::Idle &&
			stateComponent->current != ObjectState::Moving) {
			return;
		}

		std::shared_ptr<firefly::IEvent> event(new firefly::StateEvent(
			entity->getId(), ObjectState::Hyperspace));
					
		const auto eventManager = getEngine()->getEventManager();
		eventManager->registerEvent(std::move(event));
	}
}
