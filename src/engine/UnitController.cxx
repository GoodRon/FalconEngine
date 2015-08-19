/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL_events.h>

#include "UnitController.h"
#include "Unit.h"

UnitController::UnitController(WorldObject* object): Controller(object) {
}

UnitController::~UnitController() {
}

void UnitController::onEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN: {
			int x, y;
			if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				auto unit = dynamic_cast<Unit*>(m_object);
				if (unit != nullptr) {
					unit->moveTo(x, y);
				}
			}
		} break;
		default:
			break;
	}
}

