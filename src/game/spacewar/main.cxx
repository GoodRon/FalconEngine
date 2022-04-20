/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

// NOTE add particles and particle emmiters

#include <firefly/Engine.h>

#include "GameBuilder.h"

int main(int argc, char** argv) {

    // TODO catch exceptions
    auto& engine = firefly::Engine::instance();
    engine.initialize(1500, 900);

    spacewar::GameBuilder gameBuilder(&engine);
    gameBuilder.buildGame();

    engine.run();

    return 0;
}
