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
#include "UnitMovementState.h"
#include "Unit.h"

using namespace std;

int main() {
	try {
		Engine engine(300, 300);

		auto unit = new Unit;
		unit->setAnimation(atIdle, engine.getResourceManager()->
			loadAnimation("resources/boystand.json"));
		unit->setAnimation(atMovement, engine.getResourceManager()->
			loadAnimation("resources/boywalk.json"));
		unit->changeState(new UnitMovementState(20, 20));
		WorldObjectPointer unitPtr(unit);

		engine.getObjectManager()->pushObject(unitPtr);

/*
		double direction = 0.0;
		engine.getTimersPool()->addTimer(100, [&direction, unit](TimerPool::id_t) {
			direction += 10.0;
			direction = fmod(direction, 360.0);
			if (direction < 0.0) {
				direction += 360.0;
			}
			unit->setDirection(direction);
		});
*/

		return engine.execute();
	} catch (EngineException& exception) {
		cout << "Exception caught: " << exception.what() << endl;
	}
	return -1;
}
