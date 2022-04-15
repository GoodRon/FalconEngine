/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_IGAME_STATE_H
#define FALCON_IGAME_STATE_H

namespace falcon {

class Engine;

class IGameState {
public:
	IGameState(Engine* engine);
	virtual ~IGameState() = 0;

	virtual void loadResources() {}
	bool isResourcesLoaded() const;

	virtual void onEnter() {}
	virtual void onExit() {}
	virtual void update() {}

protected:
	void setResourcesLoaded(bool isLoaded);
	Engine* getEngine() const;

private:
	Engine* _engine;
	bool _isResourcesLoaded;
};

}

#endif // FALCON_IGAME_STATE_H
