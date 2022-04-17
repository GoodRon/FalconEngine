#include "GameBuilder.h"

#include <SDL.h>

#include "falcon/Engine.h"
#include "falcon/SystemManager.h"
#include "falcon/ResourceManager.h"
#include "falcon/GameObject.h"
#include "falcon/ObjectManager.h"
#include "falcon/components/Health.h"
#include "falcon/components/Position.h"
#include "falcon/components/Visual.h"
#include "falcon/components/State.h"
#include "falcon/components/Player.h"
#include "falcon/systems/PlayerControlSystem.h"

#include "EntityBuilder.h"

namespace spacewar {

class GameBuilder::Impl {
private:
	falcon::Engine* const _engine;
	bool _isBuilt;

public:
	Impl(falcon::Engine* engine):
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

		std::shared_ptr<falcon::PlayerControlSystem> playerControlSystem(
			new falcon::PlayerControlSystem(_engine));
		systemManager->addSystem(playerControlSystem);
		// TODO write me!

		return true;
	}

	bool buildGameObjects() const {
		auto objectManager = _engine->getObjectManager();
		if (!objectManager) {
			return false;
		}

		std::shared_ptr<falcon::Entity> entity;
		EntityBuilder builder(_engine);

		entity = builder.buildEntity("resources/player1.json");

		// TODO improve
		std::shared_ptr<falcon::GameObject> object(new falcon::GameObject(entity));
		objectManager->registerObject(object);

		return true;
	}
};

GameBuilder::GameBuilder(falcon::Engine* engine):
	_impl(new Impl(engine)) {
}

GameBuilder::~GameBuilder() {
}

bool GameBuilder::buildGame() {
	return _impl->buildGame();
}

}
