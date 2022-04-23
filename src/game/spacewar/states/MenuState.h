/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MENU_STATE_H
#define SW_MENU_STATE_H

#include "firefly/IGameState.h"

class MenuState: public firefly::IGameState {
public:
	MenuState();
	~MenuState() override;

	void onEnter() override;
	void onExit() override;
	void update() override;
};


#endif // SW_MENU_STATE_H
