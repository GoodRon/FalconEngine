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

		TexturePointer source = engine.getResourceManager()->loadTexture("walkvector.png");
		SDL_Rect rect = {0, 0, 32, 48};
		auto framesDown = engine.getResourceManager()->createTextureVector(
			source, rect, 0);
		auto framesLeft = engine.getResourceManager()->createTextureVector(
			source, rect, 1);
		auto framesRight = engine.getResourceManager()->createTextureVector(
			source, rect, 2);
		auto framesUp = engine.getResourceManager()->createTextureVector(
			source, rect, 3);

		Animation animationDown(framesDown, chrono::milliseconds(1000));
		Animation animationLeft(framesLeft, chrono::milliseconds(1000));
		Animation animationRight(framesRight, chrono::milliseconds(1000));
		Animation animationUp(framesUp, chrono::milliseconds(1000));

		DirectedAnimation animation;
		animation.pushAnimation(animationDown, 180.0);
		animation.pushAnimation(animationLeft, 270.0);
		animation.pushAnimation(animationRight, 90.0);
		animation.pushAnimation(animationUp, 0.0);
		animation.play();

		double direction = 0.0;
		animation.setDirection(direction);

		engine.getTimersPool()->addTimer(100, [&engine, &animation](TimerPool::id_t) {
			engine.getRenderer()->clear();
			TexturePointer frame = animation.getFrame();
			SDL_Rect source = {0, 0, 0, 0};
    		SDL_QueryTexture(frame.get(), nullptr, nullptr, &(source.w),
                     	     &(source.h));
    		SDL_Rect dest = {0, 0, source.w * 4, source.h * 4};
			engine.getRenderer()->drawTexture(frame, &source, &dest);
		});

		engine.getTimersPool()->addTimer(100, [&animation, &direction](TimerPool::id_t) {
			direction += 10.0;
			animation.setDirection(direction);
		});
	
		return engine.execute();
	} catch (EngineException& exception) {
        cout << "Exception caught: " << exception.what() << endl;
    }
    return -1;
}