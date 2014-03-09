/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <string>

union SDL_Event;
struct SDL_Window;
struct SDL_Renderer;

class Engine {
public:
	Engine();

	bool loadConfig(const std::string& file);

	int execute();

private:
	void onEvent(const SDL_Event& event);

private:
	unsigned m_width;
	unsigned m_height;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool m_run;
	bool m_init;
	int m_returnCode;
};

#endif // ENGINE_H
