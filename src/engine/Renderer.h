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

class Renderer {
public:
	static Renderer& getInstance() {
		static Renderer manager;
		return manager;
	}

	bool init(int width, int heigh);
	bool isInit() const;
	SDL_Renderer* get() const;

	SDL_Rect getPosition() const;
	void setPosition(int x, int y);

private:
	Renderer();
	~Renderer();

	Renderer(const Renderer& other) = delete;
	Renderer& operator=(Renderer& other) = delete;

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	int m_x;
	int m_y;
	int m_width;
	int m_height;
	bool m_isInit;
};

#endif // RENDERER_H
