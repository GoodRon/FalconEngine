/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <map>
#include <chrono>

//#include "IAnimation.h"

typedef std::shared_ptr<SDL_Texture> Texture;
typedef std::vector<Texture> Frames;

/**
 * @brief Класс анимации
 */
class Animation {//: public IAnimation {
public:
	enum class Direction {
		Up,
		UpRight,
		Right,
		DownRight,
		Down,
		DownLeft,
		Left,
		UpLeft
	}

	/**
	 * @brief Конструктор
	 *
	 * @param frames массив фреймов
	 * @param period период анимации
	 * @param isLooped признак цикличности
	 */
	//Animation(const std::vector<TexturePointer>& frames,
	//		  const std::chrono::milliseconds& period,
	//		  bool isLooped = true);

	Animation(const std::map<Direction, Frames>& frames,
		const std::chrono::milliseconds& period,
		bool isLooped = true);

	/**
	 * @brief Деструктор
	 */
	~Animation();

	/**
	 * @overload
	 */
	void play(bool fromStart = false);

	/**
	 * @overload
	 */
	void pause();

	/**
	 * @overload
	 */
	bool isPaused() const;

	/**
	 * @overload
	 */
	void setLoop(bool isLooped = true);

	/**
	 * @overload
	 */
	bool isLooped() const;

	/**
	 * @overload
	 */
	Texture getFrame(Direction direction);

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
	void setSpeedModificator(double speedModificator);

	/**
	 * @brief Вернуть скорость анимации
	 *
	 * @return double
	 */
	double getSpeedModificator() const;

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
	sstd::map<Direction, Frames> _frames;

	/**
	 * @brief Признак цикличности
	 */
	bool _isLooped;

	/**
	 * @brief Период всей анимации
	 */
	std::chrono::milliseconds _period;

	/**
	 * @brief Точка отсчета
	 */
	std::chrono::steady_clock::time_point _startTimepoint;

	/**
	 * @brief Смещение от точки отсчета
	 */
	std::chrono::milliseconds _timeOffset;

	/**
	 * @brief Признак остановки анимации
	 */
	bool _isPaused;

	/**
	 * @brief Модификатор скорости анимации
	 */
	double _speedModificator;
};

#endif // ANIMATION_H
