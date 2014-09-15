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

		TexturePointer textureFrames = engine.getResourceManager()->loadTexture("walk.png");
		SDL_Rect rect = {0, 0, 33, 52};
		vector<TexturePointer> frames = engine.getResourceManager()->createTextureVector(
			textureFrames, rect);

		Animation animation(frames, chrono::milliseconds(1000));
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

		return engine.execute();
	} catch (EngineException& exception) {
        cout << "Exception caught: " << exception.what() << endl;
    }
    return -1;
}
