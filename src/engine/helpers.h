/*
 * Copyright (c) 2017, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef HELPERS_H
#define HELPERS_H

#include <string>

namespace engine {
	namespace helpers {
		std::string readFile(const std::string& path);
	}
}

#endif // HELPERS_H