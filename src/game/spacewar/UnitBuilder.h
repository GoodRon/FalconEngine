/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_UNIT_BUILDER_H
#define SW_UNIT_BUILDER_H

#include <memory>
#include <string>

namespace falcon {
	class IGameObject;
}

namespace spacewar {

class UnitBuilder {
public:
	UnitBuilder();
	~UnitBuilder();

	std::shared_ptr<falcon::IGameObject> buildShip(const std::string& jsonConfig) const;

};

}

#endif // SW_UNIT_BUILDER_H
