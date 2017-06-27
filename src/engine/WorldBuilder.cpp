/*
 * Copyright (c) 2017, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "WorldBuilder.h"
#include "ResourceManager.h"
#include "Unit.h"
#include "IAnimation.h"
#include "Animation.h"
#include "AnimationType.h"
#include "helpers.h"

#include <jsoncpp/json/json.h>

using namespace std;

engine::WorldBuilder::WorldBuilder(ResourceManager* resourceManager) :
	m_resourceManager(resourceManager) {
	//m_unitBuilders() {
}

engine::WorldBuilder::~WorldBuilder() {
	//for (auto& builder: m_unitBuilders) {
	//	delete builder.second;
	//}
}

UnitPointer engine::WorldBuilder::buildUnit
	(const std::string& jsonRecipe) {
	UnitPointer unit;

	auto json = helpers::readFile(jsonRecipe);

	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(json, root)) {
		cerr << "Can't parse json from " << json << endl;
		return unit;
	}

	unit.reset(new Unit);

	Json::Value animations = root["animations"];
	for (size_t index = 0; index < animations.size(); ++index) {
		auto state = root.get("state", "").asString();
		auto file = root.get("file", "").asString();

		AnimationArray animations = 
			m_resourceManager->loadAnimation(file);
		auto type = anymationTypeFromString(state);
		unit->m_animations[type] = animations;
	}
	return unit;
}
