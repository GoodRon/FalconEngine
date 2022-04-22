#include "SpeedEvent.h"

namespace firefly {

SpeedEvent::SpeedEvent(EntityID id,
	double speed, double direction):
	IEvent(EventType::Speed),
	_id(id),
	_speed(speed),
	_direction(direction) {
}

SpeedEvent::~SpeedEvent() {
}

EntityID SpeedEvent::getId() const {
	return _id;
}

double SpeedEvent::getSpeed() const {
	return _speed;
}

double SpeedEvent::getDirection() const {
	return _direction;
}

}
