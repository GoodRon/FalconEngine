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
#include "ObjectManager.h"
#include "UnitIdleState.h"
#include "Unit.h"

using namespace std;

int main() {
	try {
		Engine engine(300, 300);

		auto animation = engine.getResourceManager()->loadAnimation("resources/boywalk.json");

		auto unit = new Unit;
		unit->setAnimation(atIdle, animation);
		unit->changeState(new UnitIdleState);
		WorldObjectPointer unitPtr(unit);

		engine.getObjectManager()->pushObject(unitPtr);
		return engine.execute();
	} catch (EngineException& exception) {
		cout << "Exception caught: " << exception.what() << endl;
	}
	return -1;
}
