/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_UNIT_BUILDER_H
#define SW_UNIT_BUILDER_H

class UnitBuilder {
public:
	UnitBuilder();
	~UnitBuilder() override {}

	falcon::IGameState buildStates() const override;
};

#endif // SW_UNIT_BUILDER_H
