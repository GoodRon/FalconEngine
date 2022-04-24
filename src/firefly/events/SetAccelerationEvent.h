/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SET_ACCELERATION_EVENT_H
#define FIREFLY_SET_ACCELERATION_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class SetAccelerationEvent final: public IEvent {
public:
	SetAccelerationEvent(EntityID id,
		double acceleration, double direction);
	~SetAccelerationEvent() override;

	EntityID getId() const;
	double getAcceleration() const;
	double getDirection() const;

private:
	const EntityID _id;
	const double _acceleration;
	const double _direction;
};

}

#endif // FIREFLY_SET_ACCELERATION_EVENT_H
