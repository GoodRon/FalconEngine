/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_IGAME_STATE_H
#define FIREFLY_IGAME_STATE_H

namespace firefly {

class Engine;

class IGameState {
public:
	IGameState();
	virtual ~IGameState() = 0;

	virtual void loadResources() {}
	bool isResourcesLoaded() const;

	virtual void onEnter() {}
	virtual void onExit() {}
	virtual void update() {}

protected:
	void setResourcesLoaded(bool isLoaded);

private:
	bool _isResourcesLoaded;
};

}

#endif // FIREFLY_IGAME_STATE_H
