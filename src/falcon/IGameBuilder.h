/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_IGAME_BUILDER_H
#define FALCON_IGAME_BUILDER_H

namespace falcon {

class IGameState;

class IGameBuilder {
public:
	IGameBuilder();
	virtual ~IGameBuilder() = 0;

	virtual std::string buildConfig() const {}
	virtual IGameState buildStates() const {}

};

}

#endif // FALCON_IGAME_BUILDER_H
