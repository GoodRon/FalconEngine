/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef DIRECTEDANIMATION_H
#define DIRECTEDANIMATION_H

#include <vector>

#include "Animation.h"

/**
 * @brief Класс направленной анимации
 */
class DirectedAnimation {
public:
	/**
 	 * @brief Конструктор
 	 */
	DirectedAnimation();

	/**
	 * @brief Добавить анимацию 
	 *
	 * @param animation
	 * @param direction направление от 0 до 360 градусов
	 * @return void
	 */
	void pushAnimation(const Animation& animation, double direction);
	
	/**
	 * @brief Начать или продолжить воспроизведение
	 *
	 * @param fromStart признак необходимости начать сначала
	 * @return void
	 */
	void play(bool fromStart = false);

	/**
	 * @brief Приостановить воспроизведение
	 *
	 * @return void
	 */
	void pause();

	/**
	 * @brief Установить признак цикличности
	 *
	 * @param isLooped
	 * @return void
	 */
	void setLoop(bool isLooped = true);

	/**
	 * @brief Установить направление
	 *
	 * @param direction от 0 до 360 градусов
	 * @return void
	 */
	void setDirection(double direction);

	/**
	 * @brief Вернуть текущий фрейм
	 *
	 * @return TexturePointer фрейм
	 */
	TexturePointer getFrame();
	
private:
	/**
	 * @brief Вектор пар направление - анимация
	 */
	std::vector<std::pair<double, Animation>> m_animations;

	/**
	 * @brief Направление
	 */
	double m_direction;
};

#endif // DIRECTEDANIMATION_H
