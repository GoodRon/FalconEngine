/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ANIMATION_TYPES_H
#define ANIMATION_TYPES_H

#include <string>

/**
 * @brief Типы анимаций
 */
enum class AnimationType {
	/**
	 * @brief Нет типа
	 */
	atNone = 0,

	/**
	 * @brief Простой
	 */
	atIdle = 1,

	/**
	 * @brief Обычное движение
	 */
	atMovement = 2
};

namespace engine {

AnimationType anymationTypeFromString(const std::string& name);

}

//enum AnimationType {
//	AnimationStand,
//	AnimationWalk,
//	AnimationRun,
//	AnimationAtackMele,
//	AnimationAtackRanged,
//	AnimationDeath,
//	AnimationTalk
//}

#endif // ANIMATION_TYPES_H
