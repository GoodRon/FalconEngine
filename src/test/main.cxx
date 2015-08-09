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
#include "TimerPool.h"

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
				default:
					break;
			}
		});

		TexturePointer background = engine.getResourceManager()->loadTexture("resources/ship.png");
		engine.getTimersPool()->addTimer(33, [&background, &engine](TimerPool::id_t) {
			SDL_Rect rsource = {0, 0, 0, 0};
			SDL_QueryTexture(background.get(), nullptr, nullptr, &(rsource.w), &(rsource.h));
			SDL_Rect rdest = engine.getRenderer()->getViewport();
			rsource.x += rdest.x;
			rsource.y += rdest.y;
			engine.getRenderer()->clear();
			engine.getRenderer()->drawTexture(background, nullptr, &rsource);
		});

		return engine.execute();
	} catch (EngineException& exception) {
		std::cout << "Exception caught: " << exception.what() << std::endl;
	}
	return -1;
}
