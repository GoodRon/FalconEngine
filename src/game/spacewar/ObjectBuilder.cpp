#include "ObjectBuilder.h"

#include "falcon/Engine.h"
#include "falcon/GameObject.h"

#include "rapidjson/document.h"

namespace spacewar {

ObjectBuilder::ObjectBuilder(falcon::Engine* engine):
	_engine(engine) {
}

ObjectBuilder::~ObjectBuilder() {
}

std::shared_ptr<falcon::IGameObject> ObjectBuilder::buildShip(
	const std::string& jsonConfig) const {
	if (!_engine) {
		return nullptr;
	}

	

	return std::shared_ptr<falcon::IGameObject>();
}

}

