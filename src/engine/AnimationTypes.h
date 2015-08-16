/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ANIMATIONTYPES_H
#define ANIMATIONTYPES_H

/**
 * @brief Типы анимаций
 */
enum AnimationType {
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

//enum AnimationType {
//	AnimationStand,
//	AnimationWalk,
//	AnimationRun,
//	AnimationAtackMele,
//	AnimationAtackRanged,
//	AnimationDeath,
//	AnimationTalk
//}

#endif // ANIMATIONTYPES_H
