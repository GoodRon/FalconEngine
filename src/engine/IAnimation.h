/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef IANIMATION_H
#define IANIMATION_H

#include <memory>

struct SDL_Texture;

/**
 * @brief Умный указатель на объект текстуры
 */
typedef std::shared_ptr<SDL_Texture> TexturePointer;

/**
 * @brief Интерфейс анимации
 */
class IAnimation {
public:
	/**
	 * @brief Начать или продолжить воспроизведение
	 *
	 * @param fromStart признак необходимости начать сначала
	 * @return void
	 */
	virtual void play(bool fromStart = false) = 0;

	/**
	 * @brief Приостановить воспроизведение
	 *
	 * @return void
	 */
	virtual void pause() = 0;

	/**
	 * @brief Вернуть признак остановки воспроизведения
	 *
	 * @return bool
	 */
	virtual bool isPaused() = 0;

	/**
	 * @brief Установить признак цикличности
	 *
	 * @param isLooped
	 * @return void
	 */
	virtual void setLoop(bool isLooped = true) = 0;

	/**
	 * @brief Вернуть признак цикличности
	 *
	 * @return bool
	 */
	virtual bool isLooped() const = 0;

	/**
	 * @brief Вернуть текущий фрейм
	 *
	 * @return TexturePointer фрейм
	 */
	virtual TexturePointer getFrame() = 0;
};

#endif // IANIMATION_H
