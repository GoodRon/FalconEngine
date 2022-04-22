/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_STATES_H
#define SW_STATES_H

namespace spacewar {

enum ObjectState {
	Idle = 0,
	Moving,
	Destroyed,
	Hyperspace
};

}

#endif // SW_STATES_H
