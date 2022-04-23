/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MAIN_STATE_H
#define SW_MAIN_STATE_H

#include <forward_list>
#include <string>

#include <firefly/IGameState.h>
#include <firefly/Types.h>

namespace firefly {
	class IEvent;
	class Engine;
}

namespace spacewar {

class MainState final: public firefly::IGameState {
public:
	MainState(firefly::Engine* engine);
	~MainState() override;

	void onEnter() override;
	void onExit() override;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	void buildObjects();
	void destroyObjects();

	void buildSystems();
	void destroySystems();

private:
	std::forward_list<firefly::EntityID> _objectIds; 
	std::forward_list<std::string> _systemNames;
};

}

#endif // SW_MAIN_STATE_H