/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <vector>
#include <iostream>

#include <SDL2/SDL.h>

#include "Engine.h"
#include "EngineException.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "UnitIdleState.h"
#include "UnitMovementState.h"
#include "Unit.h"

using namespace std;

int main() {
	try {
		Engine engine(500, 500);

		auto unit = new Unit;
		unit->setAnimation(atIdle, engine.getResourceManager()->
			loadAnimation("resources/boystand.json"));
		unit->setAnimation(atMovement, engine.getResourceManager()->
			loadAnimation("resources/boywalk.json"));
		unit->changeState(new UnitIdleState);
		unit->setSpeed(150);
		WorldObjectPointer unitPtr(unit);

		engine.getObjectManager()->pushObject(unitPtr);

		engine.pushEventHandler([&unit](const SDL_Event& event){
			switch (event.type) {
				case SDL_MOUSEBUTTONDOWN: {
					int x, y;
					if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
						if (unit != nullptr) {
							unit->moveTo(x, y);
						}
					}
				} break;
				default:
					break;
			}
		});

		return engine.execute();
	} catch (EngineException& exception) {
		cout << "Exception caught: " << exception.what() << endl;
	}
	return -1;
}
