/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <chrono>
#include <memory>
#include <string>

struct SDL_Texture;

/**
 * @brief Умный указатель на объект текстуры
 */
typedef std::shared_ptr<SDL_Texture> TexturePointer;

/**
 * @brief Класс анимации
 */
class Animation {
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
	 * @brief Пересчитать временные интервалы
	 *
	 * @return void
	 */
	 void recalculateTimes();

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
	 * @brief Вернуть признак остановки воспроизведения
	 *
	 * @return bool
	 */
	bool isPaused();

	/**
	 * @brief Установить признак цикличности
	 *
	 * @param isLooped
	 * @return void
	 */
	void setLoop(bool isLooped = true);

	/**
	 * @brief Вернуть признак цикличности
	 *
	 * @return bool
	 */
	bool isLooped() const;

	/**
	 * @brief Вернуть текущий фрейм
	 *
	 * @return TexturePointer фрейм
	 */
	TexturePointer getFrame();

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
};

#endif // ANIMATION_H
