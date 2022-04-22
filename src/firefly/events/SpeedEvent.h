/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SPEED_EVENT_H
#define FIREFLY_SPEED_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class SpeedEvent final: public IEvent {
public:
	SpeedEvent(EntityID id, 
		double speed, double direction);
	~SpeedEvent() override;

	EntityID getId() const;
	double getSpeed() const;
	double getDirection() const;

private:
	const EntityID _id;
	const double _speed;
	const double _direction;
};

}

#endif // FIREFLY_SPEED_EVENT_H
