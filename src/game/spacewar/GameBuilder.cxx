#include "GameBuilder.h"

#include <SDL.h>

#include <firefly/Engine.h>
#include <firefly/SystemManager.h>
#include <firefly/ResourceManager.h>
#include <firefly/GameObject.h>
#include <firefly/ObjectManager.h>
#include <firefly/systems/VelocitySystem.h>

#include "EntityBuilder.h"
#include "systems/PlayerControlSystem.h"
#include "systems/PositioningSystem.h"
#include "systems/GravitationalSystem.h"

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

		std::shared_ptr<PlayerControlSystem> playerControl;

		playerControl.reset(new PlayerControlSystem(_engine, 1, "1"));
		playerControl->setKeyCodes(SDLK_w, SDLK_a, SDLK_s, SDLK_d);
		systemManager->addSystem(std::move(playerControl));

		playerControl.reset(new PlayerControlSystem(_engine, 2, "2"));
		playerControl->setKeyCodes(SDLK_i, SDLK_j, SDLK_k, SDLK_l);
		systemManager->addSystem(std::move(playerControl));

		std::shared_ptr<firefly::ISystem> systemPtr;

		systemPtr.reset(new firefly::VelocitySystem(_engine));
		systemManager->addSystem(std::move(systemPtr));

		systemPtr.reset(new GravitationalSystem(_engine));
		systemManager->addSystem(std::move(systemPtr));

		systemPtr.reset(new PositioningSystem(_engine));
		systemManager->addSystem(std::move(systemPtr));
		
		// TODO write me!

		return true;
	}

	bool buildGameObjects() const {
		auto objectManager = _engine->getObjectManager();
		if (!objectManager) {
			return false;
		}

		// TODO while on a json list

		std::shared_ptr<firefly::Entity> entity;
		std::shared_ptr<firefly::GameObject> object;
		EntityBuilder builder(_engine);

		// TODO improve
		entity = builder.buildEntity("resources/background.json");
		object.reset(new firefly::GameObject(entity));
		objectManager->registerObject(object);

		entity = builder.buildEntity("resources/player1.json");
		object.reset(new firefly::GameObject(entity));
		objectManager->registerObject(object);

		entity = builder.buildEntity("resources/player2.json");
		object.reset(new firefly::GameObject(entity));
		objectManager->registerObject(object);

		entity = builder.buildEntity("resources/star.json");
		object.reset(new firefly::GameObject(entity));
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
