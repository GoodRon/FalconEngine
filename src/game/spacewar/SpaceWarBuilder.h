/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_GAME_BUILDER_H
#define SW_GAME_BUILDER_H

#include "falcon/IGameBuilder.h"

class GameBuilder: public falcon::IGameBuilder {
public:
	GameBuilder();
	~GameBuilder() override {}

	falcon::IGameState buildStates() const override;
};

#endif // SW_GAME_BUILDER_H
