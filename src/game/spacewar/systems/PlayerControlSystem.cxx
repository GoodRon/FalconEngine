#include "PlayerControlSystem.h"

#include <SDL_events.h>

#include <firefly/Entity.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/components/Player.h>
#include <firefly/components/Velocity.h>

namespace spacewar {

	PlayerControlSystem::PlayerControlSystem(
		firefly::Engine* engine) :
		firefly::ISystem("PlayerControlSystem", engine) {

		_requiredComponents.push_front(firefly::Player::ComponentName);
		_requiredComponents.push_front(firefly::Velocity::ComponentName);
	}

	PlayerControlSystem::~PlayerControlSystem() {
	}

	bool PlayerControlSystem::onEvent(
		const std::shared_ptr<firefly::IEvent>& event) const {
		if (!event) {
			return false;
		}

		if (event->getType() != firefly::EventType::NativeEvent) {
			return false;
		}

		auto nativeEvent = std::dynamic_pointer_cast<firefly::NativeEvent>(event);

		if (onPlayerOneInput(nativeEvent)) {
			return true;
		}

		if (onPlayerTwoInput(nativeEvent)) {
			return true;
		}

		return false;
	}

	bool PlayerControlSystem::onPlayerOneInput(
		const std::shared_ptr<firefly::NativeEvent>& event) const {

		const int playerId = 1;
		const double speedX = 10.0;
		const double speedY = 10.0;

		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return false;
		}

		auto sdlEvent = event->getSDLEvent();
		switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			switch (sdlEvent.key.keysym.sym) {
			case SDLK_w:
				velocityComponent->speedY = speedY;
				return true;
			case SDLK_a:
				velocityComponent->speedX = -speedX;
				return true;
			case SDLK_s:
				velocityComponent->speedY = -speedY;
				return true;
			case SDLK_d:
				velocityComponent->speedX = speedX;
				return true;
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			switch (sdlEvent.key.keysym.sym) {
			case SDLK_w:
				velocityComponent->speedY = 0.0;
				return true;
			case SDLK_a:
				velocityComponent->speedX = 0.0;
				return true;
			case SDLK_s:
				velocityComponent->speedY = 0.0;
				return true;
			case SDLK_d:
				velocityComponent->speedX = 0.0;
				return true;
			default:
				break;
			}
			break;

		default:
			break;
		}
		return false;
	}

	bool PlayerControlSystem::onPlayerTwoInput(
		const std::shared_ptr<firefly::NativeEvent>& event) const {

		const int playerId = 2;
		const double speedX = 10.0;
		const double speedY = 10.0;

		auto velocityComponent = getVelocity(playerId);
		if (!velocityComponent) {
			return false;
		}

		auto sdlEvent = event->getSDLEvent();
		switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			switch (sdlEvent.key.keysym.sym) {
			case SDLK_i:
				velocityComponent->speedY = speedY;
				return true;
			case SDLK_j:
				velocityComponent->speedX = -speedX;
				return true;
			case SDLK_k:
				velocityComponent->speedY = -speedY;
				return true;
			case SDLK_l:
				velocityComponent->speedX = speedX;
				return true;
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			switch (sdlEvent.key.keysym.sym) {
			case SDLK_i:
				velocityComponent->speedY = 0.0;
				return true;
			case SDLK_j:
				velocityComponent->speedX = 0.0;
				return true;
			case SDLK_k:
				velocityComponent->speedY = 0.0;
				return true;
			case SDLK_l:
				velocityComponent->speedX = 0.0;
				return true;
			default:
				break;
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

}
