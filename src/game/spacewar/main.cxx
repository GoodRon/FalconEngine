/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

// NOTE add particles and particle emmiters

#include <SDL_log.h>

#include <firefly/Engine.h>
#include <firefly/EngineException.h>

#include "GameBuilder.h"

int main(int argc, char** argv) {
	try {

		firefly::Engine engine(1500, 900);

		spacewar::GameBuilder gameBuilder(&engine);
		gameBuilder.buildGame();

		engine.run();

	} catch (firefly::EngineException& exception) {
		SDL_Log("Exception caught: %s", exception.what());
	}

	return 0;
}
