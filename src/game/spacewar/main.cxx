/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL_log.h>

#include <firefly/Engine.h>
#include <firefly/EngineException.h>

#include "GameBuilder.h"

int main(int, char**) {
	// TODO read from a config
	const int width = 1700;
	const int height = 1000;
	const std::string header("Space War!");
	const std::string icon("resources/icon.png");

	int ret = -1;
	try {

		firefly::Engine engine(width, height);
		engine.setWindowHeader(header);
		engine.setWindowIcon(icon);

		spacewar::GameBuilder gameBuilder(&engine);
		if (!gameBuilder.buildGame()) {
			return ret;
		}

		ret = engine.run();

	} catch (firefly::EngineException& exception) {
		SDL_Log("Engine exception caught: %s", exception.what());
	}
	return ret;
}
