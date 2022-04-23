#include "GameBuilder.h"

#include <SDL.h>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/SystemManager.h>
#include <firefly/ResourceManager.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/StateMachine.h>

#include "EntityBuilder.h"

#include "states/GameStates.h"
#include "states/MainState.h"

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

		if (!buildEntityPrototypes()) {
			return _isBuilt;
		}

		if (!buildGameStates()) {
			return _isBuilt;
		}

		_isBuilt = true;
		return _isBuilt;
	}

private:

	bool buildEntityPrototypes() const {
		const auto prototypes = _engine->getEntityPrototypes();

		// TODO while on a json list

		EntityBuilder builder(_engine);
		std::shared_ptr<firefly::Entity> entity;

		entity = builder.buildEntity("resources/background.json");
		prototypes->registerPrototype(entity->getName(), 
			std::move(entity));

		entity = builder.buildEntity("resources/player1.json");
		prototypes->registerPrototype(entity->getName(), 
			std::move(entity));

		entity = builder.buildEntity("resources/player2.json");
		prototypes->registerPrototype(entity->getName(), 
			std::move(entity));

		entity = builder.buildEntity("resources/star.json");
		prototypes->registerPrototype(entity->getName(), 
			std::move(entity));

		entity = builder.buildEntity("resources/rocket.json");
		prototypes->registerPrototype(entity->getName(), 
			std::move(entity));

		return true;
	}

	bool buildGameStates() const {

		const auto stateMachine = _engine->getStateMachine();
		std::unique_ptr<firefly::IGameState> state;

		state.reset(new MainState(_engine));
		stateMachine->pushState(std::move(state));

		stateMachine->switchState(GameState::Main);

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
