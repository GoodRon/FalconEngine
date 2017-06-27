/*
 * Copyright (c) 2017, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <map>

#include "AnimationTypes.h"

AnimationType engine::anymationTypeFromString(
	const std::string& name) {
	AnimationType type = atNone;
	
	std::map<std::string, AnimationType> types;
	types["stop"] = AnimationType::atIdle;
	types["walk"] = AnimationType::atMovement;

	for (auto &typeRow: types) {
		if (typeRow.first == name) {
			type = typeRow.second;
			break;
		}
	}
	return type;
}
