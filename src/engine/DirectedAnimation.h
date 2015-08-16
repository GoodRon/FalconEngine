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
	 * @brief Конструктор
	 */
	DirectedAnimation(const std::vector<std::pair<double, Animation>>& animations);

	/**
	 * @brief Деструктор
	 */
	virtual ~DirectedAnimation();

	// TODO remove
	void pushAnimation(const Animation& animation, double direction);

	/**
	 * @overload
	 */
	virtual void play(bool fromStart = false) override;

	/**
	 * @overload
	 */
	virtual void pause() override;

	/**
	 * @overload
	 */
	virtual bool isPaused() override;

	/**
	 * @overload
	 */
	virtual void setLoop(bool isLooped = true) override;

	/**
	 * @overload
	 */
	virtual bool isLooped() const override;

	/**
	 * @overload
	 */
	virtual TexturePointer getFrame() override;

	/**
	 * @overload
	 */
	virtual TexturePointer getFrame(double direction) override;

private:
	/**
	 * @brief Вектор пар направление - анимация
	 */
	std::vector<std::pair<double, Animation>> m_animations;

	/**
	 * @brief Последнее известное направление
	 */
	double m_lastDirection;
};

#endif // DIRECTEDANIMATION_H
