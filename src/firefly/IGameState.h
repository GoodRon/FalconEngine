/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_IGAME_STATE_H
#define FIREFLY_IGAME_STATE_H

#include <memory>

namespace firefly {

class IEvent;
class Engine;

class IGameState {
public:
	IGameState(Engine* engine);
	virtual ~IGameState() = 0;

	virtual void onEnter();
	virtual void onExit();

	virtual bool onEvent(
		const std::shared_ptr<IEvent>& event);

protected:
	Engine* getEngine() const;

private:
	Engine* const _engine;
};

}

#endif // FIREFLY_IGAME_STATE_H