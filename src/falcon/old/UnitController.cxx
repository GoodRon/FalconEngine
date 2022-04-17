/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL_events.h>

#include "UnitController.h"
#include "Unit.h"

namespace falcon {

UnitController::UnitController(WorldObject* object): 
	Controller(object) {
}

UnitController::~UnitController() {
}

void UnitController::onEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN: {
			int x, y;
			if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				auto unit = dynamic_cast<Unit*>(_object);
				if (unit != nullptr) {
					unit->moveTo(x, y);
				}
			}
		} break;
		default:
			break;
	}
}

}
