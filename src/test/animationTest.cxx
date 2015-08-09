/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <vector>
#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

#include "Engine.h"
#include "EngineException.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "TimerPool.h"
#include "Renderer.h"

using namespace std;

int main() {
	try {
		Engine engine(300, 300);

		TexturePointer textureFrames = engine.getResourceManager()->loadTexture("resources/walk.png");
		SDL_Rect rect = {0, 0, 33, 52};
		auto frames = engine.getResourceManager()->createTextureMap(textureFrames, rect);

		Animation animation(frames[0], chrono::milliseconds(1000));
		animation.play();

		engine.getTimersPool()->addTimer(100, [&engine, &animation](TimerPool::id_t) {
			engine.getRenderer()->clear();
			TexturePointer frame = animation.getFrame();
			SDL_Rect source = {0, 0, 0, 0};
			SDL_QueryTexture(frame.get(), nullptr, nullptr, &(source.w),
							 &(source.h));
			SDL_Rect dest = {0, 0, source.w * 4, source.h * 4};
			engine.getRenderer()->drawTexture(frame, &source, &dest);
		});

		double animationSpeed = 1.0;
		engine.pushEventHandler([&engine, &animationSpeed, &animation]
								(const SDL_Event& event) {
			double delta = 0.1;
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							animationSpeed += delta;
							animation.setSpeed(animationSpeed);
							break;
						case SDLK_DOWN:
							animationSpeed -= delta;
							if (animationSpeed < 1.0) {
								animationSpeed = 1.0;
							}
							animation.setSpeed(animationSpeed);
							break;
						default:
							break;
					}
					break;
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
