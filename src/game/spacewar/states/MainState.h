/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MAIN_STATE_H
#define SW_MAIN_STATE_H

#include <firefly/IGameState.h>

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
	
};

}

#endif // SW_MAIN_STATE_H