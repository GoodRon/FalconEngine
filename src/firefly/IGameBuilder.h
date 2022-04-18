/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_IGAME_BUILDER_H
#define FIREFLY_IGAME_BUILDER_H

namespace firefly {

class IGameState;

class IGameBuilder {
public:
	IGameBuilder();
	virtual ~IGameBuilder() = 0;

	virtual std::string buildConfig() const {}
	virtual IGameState buildStates() const {}

};

}

#endif // FIREFLY_IGAME_BUILDER_H
