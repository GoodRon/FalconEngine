#include "GameBuilder.h"

#include <SDL.h>

#include "falcon/Engine.h"
#include "falcon/ComponentRegistry.h"
#include "falcon/components/Health.h"
#include "falcon/components/Position.h"
#include "falcon/components/Visual.h"

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
		if (!_engine) {
			return false;
		}

		if (_isBuilt) {
			return true;
		}

		_isBuilt = registerComponents(_engine->getComponentRegistry());

		return _isBuilt;
	}

private:
	bool registerComponents(falcon::ComponentRegistry* registry) {
		if (!registry) {
			return false;
		}

		registry->registerComponent<falcon::Health>();
		registry->registerComponent<falcon::Position>();
		registry->registerComponent<falcon::Visual>();

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
