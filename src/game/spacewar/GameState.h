/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_GAME_STATE_H
#define SW_GAME_STATE_H

#include <memory>

#include "firefly/IGameState.h"

class GameState: public firefly::IGameState {
public:
	GameState();
	~GameState() override;

	GameState(GameState&&) = default;
	GameState& operator=(GameState&&) = default;

	void loadResources() override;

	void onEnter() override;
	void onExit() override;
	void update() override;

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

#endif // SW_GAME_STATE_H
