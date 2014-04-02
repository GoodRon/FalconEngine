/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ENGINEEXCEPTION_H
#define ENGINEEXCEPTION_H

#include <stdexcept>
#include <string>

class EngineException : public std::runtime_error {
public:
	EngineException(const std::string& what) : std::runtime_error(what) {}
};

#endif // ENGINEEXCEPTION_H
