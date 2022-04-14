/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <vector>
#include <chrono>
#include <iostream>

#include <SDL.h>

#include "Engine.h"
#include "EngineException.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "TimerPool.h"
#include "Renderer.h"

using namespace std;

int main(int argc, char** argv) {
	try {
		falcon::Engine engine(300, 300);

		auto animation = engine.getResourceManager()->loadAnimation("resources/boywalk.json");
		animation->play();

		engine.getTimersPool()->addTimer(50, [&engine, &animation](falcon::TimerPool::id_t) {
			engine.getRenderer()->clearViewport();
			falcon::TexturePointer frame = animation->getFrame(180.0);
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
							//animation->setSpeed(animationSpeed);
							break;
						case SDLK_DOWN:
							animationSpeed -= delta;
							if (animationSpeed < 1.0) {
								animationSpeed = 1.0;
							}
							//animation->setSpeed(animationSpeed);
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
	} catch (falcon::EngineException& exception) {
		cout << "Exception caught: " << exception.what() << endl;
	}
	return -1;
}
