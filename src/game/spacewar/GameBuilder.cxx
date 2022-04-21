#include "GameBuilder.h"

#include <SDL.h>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/SystemManager.h>
#include <firefly/ResourceManager.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>

#include "EntityBuilder.h"
#include "systems/PlayerControlSystem.h"
#include "systems/PositioningSystem.h"
#include "systems/GravitationalSystem.h"
#include "systems/ShipStateSystem.h"
#include "systems/LifetimeSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/VelocitySystem.h"

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
		playerControl->setKeyCodes(SDLK_w, SDLK_a, SDLK_s, SDLK_d, SDLK_SPACE);
		systemManager->addSystem(std::move(playerControl));

		playerControl.reset(new PlayerControlSystem(_engine, 2, "2"));
		playerControl->setKeyCodes(SDLK_KP_8, SDLK_KP_4, 
			SDLK_KP_5, SDLK_KP_6, SDLK_KP_ENTER);
		systemManager->addSystem(std::move(playerControl));

		std::shared_ptr<firefly::ISystem> systemPtr;

		systemPtr.reset(new VelocitySystem(_engine));
		systemManager->addSystem(std::move(systemPtr));

		systemPtr.reset(new GravitationalSystem(_engine));
		systemManager->addSystem(std::move(systemPtr));

		systemPtr.reset(new PositioningSystem(_engine));
		systemManager->addSystem(std::move(systemPtr));

		systemPtr.reset(new ShipStateSystem(_engine));
		systemManager->addSystem(std::move(systemPtr));
		
		systemPtr.reset(new LifetimeSystem(_engine));
		systemManager->addSystem(std::move(systemPtr));

		systemPtr.reset(new CollisionSystem(_engine));
		systemManager->addSystem(std::move(systemPtr));

		return true;
	}

	bool buildGameObjects() const {
		auto entityManager = _engine->getEntityManager();
		if (!entityManager) {
			return false;
		}

		auto entityPrototypes = _engine->getEntityPrototypes();
		if (!entityPrototypes) {
			return false;
		}

		// TODO while on a json list

		std::shared_ptr<firefly::Entity> entity;
		EntityBuilder builder(_engine);

		entity = builder.buildEntity("resources/background.json");
		entityManager->addEntity(std::move(entity));

		entity = builder.buildEntity("resources/player1.json");
		entityManager->addEntity(std::move(entity));

		entity = builder.buildEntity("resources/player2.json");
		entityManager->addEntity(std::move(entity));

		entity = builder.buildEntity("resources/star.json");
		entityManager->addEntity(std::move(entity));

		entity = builder.buildEntity("resources/rocket.json");
		entityPrototypes->registerPrototype(entity->getName(), 
			std::move(entity));

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
