#include "GameState.h"

class GameState::Impl {
private:
	GameState* _parent;

	// NOTE bacground, stars, ships, particles

public:
	Impl(GameState* parent) :
		_parent(parent) {

	}

	~Impl() {

	}

	Impl(const Impl&) = delete;
	Impl& operator=(const Impl&) = delete;

	void loadResources() {

	}

	void onEnter() {

	}

	void onExit() {

	}

	void update() {

	}
};

GameState::GameState():
	falcon::IGameState(),
	_impl(new Impl(this)) {
}

GameState::~GameState() {
}

void GameState::loadResources() {
	_impl->loadResources();
}

void GameState::onEnter() {
	_impl->onEnter();
}

void GameState::onExit() {
	_impl->onExit();
}

void GameState::update() {
	_impl->update();
}
