/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;

/**
 * @brief Класс рендерера
 */
class Renderer {
public:
	/**
	 * @brief Вернуть ссылку на объект синглтона
	 * @return Renderer&
	 */
	static Renderer& getInstance() {
		static Renderer manager;
		return manager;
	}

	/**
	 * @brief Инициализировать рендерер
	 * 
	 * @param width ширина порта вывода
	 * @param heigh высота порта вывода
	 * 
	 * @return bool
	 */
	bool init(int width, int heigh);

	/**
	 * @brief Проверка инициализации рендерера
	 * @return bool
	 */
	bool isInit() const;

	/**
	 * @brief Вернуть указатель на объект SDL_Renderer
	 * @return SDL_Renderer*
	 */
	SDL_Renderer* get() const;

	/**
	 * @brief Вернуть положение в мировом пространстве
	 * @return SDL_Rect
	 */
	SDL_Rect getPosition() const;

	/**
	 * @brief Установить положение в мировом пространстве
	 * 
	 * @param SDL_Rect Учитываются только поля x и y
	 */
	void setPosition(const SDL_Rect& position);

	/**
	 * @brief Установить положение в мировом пространстве
	 * 
	 * @param x
	 * @param y
	 */
	void setPosition(int x, int y);

private:
	/**
	 * @brief Конструктор
	 */
	Renderer();

	/**
	 * @brief Деструктор
	 */
	~Renderer();

	/**
	 * @brief Копирующий конструктор
	 * 
	 * @param other
	 */
	Renderer(const Renderer& other) = delete;

	/**
	 * @brief Оператор присваивания
	 * 
	 * @param other
	 */
	Renderer& operator=(Renderer& other) = delete;

private:
	/**
	 * @brief Окно вывода
	 */
	SDL_Window* m_window;

	/**
	 * @brief Объект рендерера
	 */
	SDL_Renderer* m_renderer;

	/**
	 * @brief Ширина, высота и положение в мировом пространстве
	 */
	SDL_Rect m_rect;

	/**
	 * @brief Признак инициализации
	 */
	bool m_isInit;
};

#endif // RENDERER_H
