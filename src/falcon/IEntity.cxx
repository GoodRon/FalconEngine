#include "IEntity.h"

#include <random>

namespace falcon {

IEntity::IEntity():
	_id(0) {

	// TODO check collisions

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis;
	_id = dis(gen);
}

IEntity::~IEntity() {
}

EntityID IEntity::getId() const {
	return _id;
}

}
