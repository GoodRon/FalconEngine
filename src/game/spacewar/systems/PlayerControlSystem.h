/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_PLAYER_CONTROL_H
#define SW_SYSTEMS_PLAYER_CONTROL_H

#include <memory>

namespace falcon {
	class Engine;
}

namespace spacewar {

class GameBuilder {
public:
	GameBuilder(falcon::Engine* engine);
	~GameBuilder();

	GameBuilder(const GameBuilder&) = delete;
	GameBuilder& operator=(const GameBuilder&) = delete;

	bool buildGame();

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

}

#endif // SW_SYSTEMS_PLAYER_CONTROL_H
