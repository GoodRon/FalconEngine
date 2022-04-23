/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_IGAME_STATE_H
#define FIREFLY_IGAME_STATE_H

#include <memory>
#include <string>
#include <forward_list>

#include "Types.h"

namespace firefly {

class IEvent;
class Engine;

class IGameState {
public:
	IGameState(Engine* engine, int id);
	virtual ~IGameState() = 0;

	IGameState(const IGameState&) = delete;
	IGameState& operator=(IGameState&) = delete;

	int getId() const;

	void init();
	bool isInit() const;

	virtual void onEnter();
	virtual void onExit();

	virtual bool onEvent(
		const std::shared_ptr<IEvent>& event);

protected:
	Engine* getEngine() const;

	virtual void buildObjects();
	void setObjectIds(
		std::forward_list<EntityID>&& objectIds);
	void destroyObjects();
	void setObjectsActive(bool isActive) const;

	virtual void buildSystems();
	void setSystemNames(
		std::forward_list<std::string>&& systemNames);
	void destroySystems();
	void setSystemsActive(bool isActive) const;

private:
	Engine* const _engine;
	const int _id;
	bool _isInit;
	std::forward_list<firefly::EntityID> _objectIds; 
	std::forward_list<std::string> _systemNames;
};

}

#endif // FIREFLY_IGAME_STATE_H