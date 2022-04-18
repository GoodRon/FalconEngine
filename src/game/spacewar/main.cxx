/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

// NOTE particles and particle emmiters

#include <SDL.h>

#include <iostream>

#include "falcon/Engine.h"

#include "GameBuilder.h"

int main(int argc, char** argv) {

    auto& engine = falcon::Engine::instance();
    engine.initialize(500, 500);

    spacewar::GameBuilder gameBuilder(&engine);
    gameBuilder.buildGame();

    engine.run();

    return 0;
}
