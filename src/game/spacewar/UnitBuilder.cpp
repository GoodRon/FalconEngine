#include "UnitBuilder.h"

#include "falcon/IGameObject.h"

namespace spacewar {

UnitBuilder::UnitBuilder() {

}

UnitBuilder::~UnitBuilder() {

}

std::shared_ptr<falcon::IGameObject> UnitBuilder::buildShip(
	const std::string& jsonConfig) const {


	return std::shared_ptr<falcon::IGameObject>();
}

}

