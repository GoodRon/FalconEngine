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
struct SDL_Texture;

typedef std::shared_ptr<SDL_Texture> TexturePointer;

// TODO rename to viewport
/**
 * @brief Класс рендерера
 */
class Renderer {
public:
	/**
	 * @brief Конструктор
	 * 
	 * @param width ширина порта вывода
	 * @param heigh высота порта вывода
	 */
	Renderer(int width, int heigh);

	/**
	 * @brief Деструктор
	 */
	~Renderer();

	/**
	 * @brief Очистка
	 * 
	 * @return  bool
	 */
	bool clear();

	/**
	 * @brief Отрисовать текстуру
	 * @details [long description]
	 * 
	 * @param texture текстура
	 * @param source область текстуры (nullptr - вся текстура)
	 * @param destination область вывода (nullptr - все окно)
	 * @return bool
	 */
	bool drawTexture(TexturePointer& texture, SDL_Rect* source, 
		SDL_Rect* destination);

	/**
	 * @brief Вернуть указатель на объект SDL_Renderer
	 * @return SDL_Renderer*
	 */
	SDL_Renderer* getContext() const;

	/**
	 * @brief Вернуть порт вывода
	 * @return SDL_Rect
	 */
	SDL_Rect getViewport() const;

	/**
	 * @brief Установить порт вывода
	 * 
	 * @param SDL_Rect
	 */
	void setViewport(const SDL_Rect& viewport);

private:
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
	SDL_Rect m_viewport;
};

#endif // RENDERER_H