#include "GameBuilder.h"

#include <SDL.h>

#include "firefly/Engine.h"
#include "firefly/SystemManager.h"
#include "firefly/ResourceManager.h"
#include "firefly/GameObject.h"
#include "firefly/ObjectManager.h"
#include "firefly/components/Health.h"
#include "firefly/components/Position.h"
#include "firefly/components/Visual.h"
#include "firefly/components/State.h"
#include "firefly/components/Player.h"
#include "firefly/systems/PlayerControlSystem.h"

#include "EntityBuilder.h"

namespace spacewar {

class GameBuilder::Impl {
private:
	firefly::Engine* const _engine;
	bool _isBuilt;

public:
	Impl(firefly::Engine* engine):
		_engine(engine),
		_isBuilt(false) {

	}

	~Impl() {
	}

	Impl(const Impl&) = delete;
	Impl& operator=(const Impl&) = delete;

	bool buildGame() {
		if (_isBuilt) {
			return _isBuilt;
		}

		if (!_engine) {
			return _isBuilt;
		}

		// TODO return some error code && clean the engine mb

		if (!registerSystems()) {
			return _isBuilt;
		}

		if (!buildGameObjects()) {
			return _isBuilt;
		}

		_isBuilt = true;
		return _isBuilt;
	}

private:

	bool registerSystems() const {
		auto systemManager = _engine->getSystemManager();
		if (!systemManager) {
			return false;
		}

		std::shared_ptr<firefly::PlayerControlSystem> playerControlSystem(
			new firefly::PlayerControlSystem(_engine));
		systemManager->addSystem(playerControlSystem);
		// TODO write me!

		return true;
	}

	bool buildGameObjects() const {
		auto objectManager = _engine->getObjectManager();
		if (!objectManager) {
			return false;
		}

		std::shared_ptr<firefly::Entity> entity;
		EntityBuilder builder(_engine);

		entity = builder.buildEntity("resources/player1.json");

		// TODO improve
		std::shared_ptr<firefly::GameObject> object(new firefly::GameObject(entity));
		objectManager->registerObject(object);

		return true;
	}
};

GameBuilder::GameBuilder(firefly::Engine* engine):
	_impl(new Impl(engine)) {
}

GameBuilder::~GameBuilder() {
}

bool GameBuilder::buildGame() {
	return _impl->buildGame();
}

}
