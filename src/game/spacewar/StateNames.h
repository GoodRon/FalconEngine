/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_STATES_H
#define SW_SYSTEMS_STATES_H

#include <string>

namespace spacewar {

const std::string stateNameIdle();
const std::string stateNameMoving();
const std::string stateNameHyperspace();
const std::string stateNameDestroyed();

}

#endif // SW_SYSTEMS_STATES_H
