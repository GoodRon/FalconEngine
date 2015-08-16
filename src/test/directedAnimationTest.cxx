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
#include "DirectedAnimation.h"
#include "TimerPool.h"
#include "Renderer.h"

using namespace std;

int main() {
	try {
		Engine engine(300, 300);

		auto animation3 = engine.getResourceManager()->loadAnimation("resources/boywalk.json");
		auto animation2 = engine.getResourceManager()->loadAnimation("resources/boywalk.json");
		auto animation = engine.getResourceManager()->loadAnimation("resources/boywalk.json");
		animation->play();

		double direction = 0.0;

		engine.getTimersPool()->addTimer(100, [&engine, &animation, &direction](TimerPool::id_t) {
			engine.getRenderer()->clearViewport();
			TexturePointer frame = animation->getFrame(direction);
			SDL_Rect source = {0, 0, 0, 0};
			SDL_QueryTexture(frame.get(), nullptr, nullptr, &(source.w),
							 &(source.h));
			SDL_Rect dest = {0, 0, source.w * 4, source.h * 4};
			engine.getRenderer()->drawTexture(frame, &source, &dest);
		});

		engine.getTimersPool()->addTimer(100, [&direction](TimerPool::id_t) {
			direction += 10.0;
		});

		return engine.execute();
	} catch (EngineException& exception) {
		cout << "Exception caught: " << exception.what() << endl;
	}
	return -1;
}
