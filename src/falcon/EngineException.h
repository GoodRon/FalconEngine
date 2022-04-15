/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ENGINE_EXCEPTION_H
#define FALCON_ENGINE_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace falcon {

class EngineException: public std::runtime_error {
public:
	EngineException(const std::string& what) : std::runtime_error(what) {}
};

}

#endif // FALCON_ENGINE_EXCEPTION_H
