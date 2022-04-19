/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

// NOTE particles and particle emmiters

#include <SDL.h>

#include <iostream>

#include "firefly/Engine.h"

#include "GameBuilder.h"

int main(int argc, char** argv) {

    // TODO catch exceptions
    auto& engine = firefly::Engine::instance();
    engine.initialize(1000, 700);

    spacewar::GameBuilder gameBuilder(&engine);
    gameBuilder.buildGame();

    engine.run();

    return 0;
}
