#include "StateNames.h"

namespace spacewar {

static const std::string Idle = "Idle";
static const std::string Moving = "Moving";
static const std::string Hyperspace = "Hyperspace";
static const std::string Destroyed = "Destroyed";

const std::string stateNameIdle() {
	return Idle;
}

const std::string stateNameMoving() {
	return Moving;
}

const std::string stateNameHyperspace() {
	return Hyperspace;
}

const std::string stateNameDestroyed() {
	return Destroyed;
}

}