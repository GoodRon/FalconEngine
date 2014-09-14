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
	 * @param frameTime время проигрывания одного фрейма
	 * @param isLooped признак цикличности
	 */
	Animation(const std::vector<TexturePointer>& frames, 
			  const std::chrono::milliseconds& frameTime, 
			  bool isLooped = true);

	// TODO write it!
	/**
	 * @brief Конструктор из json
	 *
	 * @param jsonFile путь к json
	 */
//	Animation(const std::string& jsonFile);

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
	 * @brief Время проигрывания одного фрейма
	 */
	std::chrono::milliseconds m_frameTime;

	/**
	 * @brief Признак цикличности
	 */
	bool m_isLooped;

	/**
	 * @brief Рассчитанный период всей анимации
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
	 * @brief Признак остановки проигрывания анимации
	 */
	bool m_isPaused;
};

#endif // ANIMATION_H
