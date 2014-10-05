/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef DIRECTEDANIMATION_H
#define DIRECTEDANIMATION_H

#include "Animation.h"

/**
 * @brief Класс направленной анимации
 */
class DirectedAnimation : public IAnimation {
public:
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
	virtual void play(bool fromStart = false) override;

	/**
	 * @brief Приостановить воспроизведение
	 *
	 * @return void
	 */
	virtual void pause() override;

	/**
	 * @brief Вернуть признак остановки воспроизведения
	 *
	 * @return bool
	 */
	virtual bool isPaused() override;

	/**
	 * @brief Установить признак цикличности
	 *
	 * @param isLooped
	 * @return void
	 */
	virtual void setLoop(bool isLooped = true) override;

	/**
	 * @brief Вернуть признак цикличности
	 *
	 * @return bool
	 */
	virtual bool isLooped() const override;

	/**
	 * @brief Вернуть текущий фрейм
	 *
	 * @return TexturePointer фрейм
	 */
	virtual TexturePointer getFrame() override;

	/**
	 * @brief Установить направление
	 *
	 * @param direction от 0 до 360 градусов
	 * @return void
	 */
	void setDirection(double direction);

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
