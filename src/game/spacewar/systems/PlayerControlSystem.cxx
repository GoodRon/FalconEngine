#include "PlayerControlSystem.h"

#include <SDL_events.h>

#include <firefly/Entity.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/components/Player.h>
#include <firefly/components/Velocity.h>

namespace spacewar {

PlayerControlSystem::PlayerControlSystem(
	firefly::Engine* engine):
	firefly::ISystem("PlayerControl", engine) {

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
	const double accelerationX = 10.0;
	const double accelerationY = 10.0;

	auto sdlEvent = event->getSDLEvent();
	switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			switch (sdlEvent.key.keysym.sym) {
				case SDLK_w:
					setAccelerationY(playerId, accelerationY);
					return true;
				case SDLK_a:
					setAccelerationX(playerId, -accelerationX);
					return true;
				case SDLK_s:
					setAccelerationY(playerId, -accelerationY);
					return true;
				case SDLK_d:
					setAccelerationX(playerId, accelerationX);
					return true;
				default:
					break;
			}
			break;

		case SDL_KEYUP:
			switch (sdlEvent.key.keysym.sym) {
				case SDLK_w:
					setAccelerationY(playerId, 0.0);
					return true;
				case SDLK_a:
					setAccelerationX(playerId, 0.0);
					return true;
				case SDLK_s:
					setAccelerationY(playerId, 0.0);
					return true;
				case SDLK_d:
					setAccelerationX(playerId, 0.0);
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
	const double accelerationX = 10.0;
	const double accelerationY = 10.0;

	auto sdlEvent = event->getSDLEvent();
	switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			switch (sdlEvent.key.keysym.sym) {
				case SDLK_i:
					setAccelerationY(playerId, accelerationY);
					return true;
				case SDLK_j:
					setAccelerationX(playerId, -accelerationX);
					return true;
				case SDLK_k:
					setAccelerationY(playerId, -accelerationY);
					return true;
				case SDLK_l:
					setAccelerationX(playerId, accelerationX);
					return true;
				default:
					break;
			}
			break;

		case SDL_KEYUP:
			switch (sdlEvent.key.keysym.sym) {
				case SDLK_i:
					setAccelerationY(playerId, 0.0);
					return true;
				case SDLK_j:
					setAccelerationX(playerId, 0.0);
					return true;
				case SDLK_k:
					setAccelerationY(playerId, 0.0);
					return true;
				case SDLK_l:
					setAccelerationX(playerId, 0.0);
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
	for (auto& entity: _entities) {
		auto playerComponent = static_cast<firefly::Player*>(
			entity.second->getComponent(
				firefly::getComponentId(firefly::Player::ComponentName)));

		if (playerComponent->playerId == playerId) {
			return entity.second;
		}
	}
	return nullptr;
}

void PlayerControlSystem::setAccelerationX(
	int playerId, double accelerationX) const {

	firefly::Entity* playerEntity = findPlayer(playerId);
	if (!playerEntity) {
		return;
	}

	auto velocityComponent = static_cast<firefly::Velocity*>(
		playerEntity->getComponent(
			firefly::getComponentId(firefly::Velocity::ComponentName)));

	velocityComponent->accelerationX = accelerationX;
}

void PlayerControlSystem::setAccelerationY(
	int playerId, double accelerationY) const {

	firefly::Entity* playerEntity = findPlayer(playerId);
	if (!playerEntity) {
		return;
	}

	auto velocityComponent = static_cast<firefly::Velocity*>(
		playerEntity->getComponent(
			firefly::getComponentId(firefly::Velocity::ComponentName)));

	velocityComponent->accelerationY = accelerationY;
}

}
