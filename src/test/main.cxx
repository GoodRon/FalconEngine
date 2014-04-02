/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>

#include "Engine.h"
#include "EngineException.h"

int main() {
	int returnCode = -1;
	try {
		Engine engine;
		returnCode = engine.execute();
	} catch (EngineException& exception) {
		std::cout << "Exception caught: " << exception.what() << std::endl;
	}
	return returnCode;
}
