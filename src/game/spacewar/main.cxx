/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL_log.h>

#include <firefly/Engine.h>
#include <firefly/EngineException.h>

#include "GameBuilder.h"

int main(int, char**) {
	const int width = 1500;
	const int height = 900;
	const std::string header("Space War!");
	const std::string icon("resources/icon.png");

	int ret = 0;
	try {

		firefly::Engine engine(width, height);
		engine.setWindowHeader(header);
		engine.setWindowIcon(icon);

		spacewar::GameBuilder gameBuilder(&engine);
		gameBuilder.buildGame();

		ret = engine.run();

	} catch (firefly::EngineException& exception) {
		SDL_Log("Exception caught: %s", exception.what());
		ret = -1;
	}
	return ret;
}
