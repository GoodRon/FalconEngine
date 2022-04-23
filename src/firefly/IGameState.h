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
	IGameState(Engine* engine, int id);
	virtual ~IGameState() = 0;

	IGameState(const IGameState&) = delete;
	IGameState& operator=(IGameState&) = delete;

	virtual void onEnter();
	virtual void onExit();

	int getId() const;

	virtual bool onEvent(
		const std::shared_ptr<IEvent>& event);

protected:
	Engine* getEngine() const;

private:
	Engine* const _engine;
	const int _id;
};

}

#endif // FIREFLY_IGAME_STATE_H