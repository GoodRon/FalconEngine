/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <chrono>

#include "IAnimation.h"

/**
 * @brief Класс анимации
 */
class Animation : public IAnimation {
public:
	/**
	 * @brief Конструктор
	 *
	 * @param frames массив фреймов
	 * @param period период анимации
	 * @param isLooped признак цикличности
	 */
	Animation(const std::vector<TexturePointer>& frames,
			  const std::chrono::milliseconds& period,
			  bool isLooped = true);

	/**
	 * @brief Деструктор
	 */
	virtual ~Animation();

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
	 * @brief Установить период для анимации
	 *
	 * @param period
	 * @return void
	 */
	void setPeriod(const std::chrono::milliseconds& period);

	/**
	 * @brief Вернуть период анимации
	 *
	 * @return std::chrono::milliseconds
	 */
	std::chrono::milliseconds getPeriod() const;

	/**
	 * @brief Вернуть оставшееся время
	 *
	 * @return std::chrono::milliseconds
	 */
	std::chrono::milliseconds getRemainingTime();

	/**
	 * @brief Установить скорость анимации
	 *
	 * @param speed
	 * @return void
	 */
	void setSpeed(double speed);

	/**
	 * @brief Вернуть скорость анимации
	 *
	 * @return double
	 */
	double getSpeed() const;

	void setDirection(double direction);

	double getDirection() const;

private:
	/**
	 * @brief Пересчитать временные интервалы
	 *
	 * @return void
	 */
	 void recalculateTimes();

private:
	/**
	 * @brief Фреймы
	 */
	std::vector<TexturePointer> m_frames;

	/**
	 * @brief Признак цикличности
	 */
	bool m_isLooped;

	/**
	 * @brief Период всей анимации
	 */
	std::chrono::milliseconds m_period;

	/**
	 * @brief Точка отсчета
	 */
	std::chrono::steady_clock::time_point m_startTimepoint;

	/**
	 * @brief Смещение от точки отсчета
	 */
	std::chrono::milliseconds m_timeOffset;

	/**
	 * @brief Признак остановки анимации
	 */
	bool m_isPaused;

	/**
	 * @brief Модификатор скорости анимации
	 */
	double m_speed;

	double m_direction;
};

#endif // ANIMATION_H
