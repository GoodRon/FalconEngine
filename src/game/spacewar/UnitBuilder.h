/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_UNIT_BUILDER_H
#define SW_UNIT_BUILDER_H

class UnitBuilder {
public:
	UnitBuilder();
	~UnitBuilder();

	Ship buildShip(const std::string& jsonConfig) const;

};

#endif // SW_UNIT_BUILDER_H
