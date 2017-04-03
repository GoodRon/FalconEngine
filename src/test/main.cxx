/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>

#include <SDL2/SDL.h>

#include "Engine.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EngineException.h"
#include "ObjectManager.h"
#include "WorldObject.h"
#include "Tile.h"
#include "TimerPool.h"

using namespace std;

int main() {
	try {
		Engine engine;
		engine.pushEventHandler([&engine](const SDL_Event& event) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							if (engine.getRenderer()) {
								SDL_Rect rdest = engine.getRenderer()->getViewport();
								rdest.y += 5;
								engine.getRenderer()->setViewport(rdest);
							}
							break;
						case SDLK_DOWN:
							if (engine.getRenderer()) {
								SDL_Rect rdest = engine.getRenderer()->getViewport();
								rdest.y -= 5;
								engine.getRenderer()->setViewport(rdest);
							}
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN: {
					int x, y;
					if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
						auto object = engine.getObjectManager()->getObjectByCoordinates(x, y);
						if (object) {
							object->setVisibility(!object->isVisible());
						}
					}
				} break;
				default:
					break;
			}
		});

		TexturePointer texture =
				engine.getResourceManager()->loadTexture("resources/ship.png");
		WorldObjectPointer ship(new Tile(texture));
		engine.getObjectManager()->pushObject(ship);

		engine.getTimersPool()->addTimer(33, [&engine](TimerPool::id_t) {
			engine.getRenderer()->clearViewport();
			engine.getObjectManager()->drawAllObjects();
		});

//		SDL_ShowCursor(SDL_ENABLE);

		return engine.execute();
	} catch (EngineException& exception) {
		cout << "Exception caught: " << exception.what() << endl;
	}
	return -1;
}
