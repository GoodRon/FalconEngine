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
		Engine engine(200, 200);

		vector<TexturePointer> frames;
		// TODO сделать загрузку вектором
		frames.push_back(engine.getResourceManager()->loadTexture("walk1.png"));
		frames.push_back(engine.getResourceManager()->loadTexture("walk2.png"));
		frames.push_back(engine.getResourceManager()->loadTexture("walk3.png"));
		Animation animation(frames, chrono::milliseconds(333));

		engine.getTimersPool()->addTimer(100, [&engine, &animation](TimerPool::id_t) {
			engine.getRenderer()->clear();
			TexturePointer frame = animation.getFrame();
			SDL_Rect source = {0, 0, 0, 0};
    		SDL_QueryTexture(frame.get(), nullptr, nullptr, &(source.w),
                     	     &(source.h));
    		SDL_Rect dest = {0, 0, source.w * 4, source.h * 4};
			engine.getRenderer()->drawTexture(frame, &source, &dest);
		});

		return engine.execute();
	} catch (EngineException& exception) {
        std::cout << "Exception caught: " << exception.what() << std::endl;
    }
    return -1;
}
