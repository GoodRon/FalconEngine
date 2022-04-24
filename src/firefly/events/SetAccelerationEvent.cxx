#include "SetAccelerationEvent.h"

namespace firefly {

SetAccelerationEvent::SetAccelerationEvent(EntityID id,
	double acceleration, double direction):
	IEvent(EventType::SetAcceleration),
	_id(id),
	_acceleration(acceleration),
	_direction(direction) {
}

SetAccelerationEvent::~SetAccelerationEvent() {
}

EntityID SetAccelerationEvent::getId() const {
	return _id;
}

double SetAccelerationEvent::getAcceleration() const {
	return _acceleration;
}

double SetAccelerationEvent::getDirection() const {
	return _direction;
}

}
