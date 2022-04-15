/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <vector>
#include <iostream>

#include <SDL.h>

#include "Engine.h"
#include "EngineException.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "UnitIdleState.h"
#include "UnitMovementState.h"
#include "Unit.h"

using namespace std;

int main(int argc, char** argv) {
	try {
		auto& engine = falcon::Engine::instance();
		engine.initialize(500, 500);

		std::shared_ptr<falcon::Unit> unit(new falcon::Unit);

		unit->setAnimation(falcon::AnimationType::Idle, engine.getResourceManager()->
			loadAnimation("resources/boystand.json"));
		unit->setAnimation(falcon::AnimationType::Movement, engine.getResourceManager()->
			loadAnimation("resources/boywalk.json"));

		std::unique_ptr<falcon::State<falcon::Unit>> state(new falcon::UnitIdleState);
		unit->changeState(std::move(state));
		unit->setSpeed(150);
		
		engine.getObjectManager()->push(unit);

		double scale = 1.0;

		engine.pushEventHandler([&unit, &scale](const SDL_Event& event)->bool{
			switch (event.type) {
				case SDL_MOUSEBUTTONDOWN: {
					int x, y;
					if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
						if (unit != nullptr) {
							unit->moveTo(x, y);
							return true;
						}
					}
				} break;
				case SDL_MOUSEWHEEL:
					scale += 0.25 * event.wheel.y;
					unit->setScale(scale);
					return true;
				default:
					break;
			}
			return false;
		});

		return engine.run();
	} catch (falcon::EngineException& exception) {
		cout << "Exception caught: " << exception.what() << endl;
	}
	return -1;
}
