/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <string>

union SDL_Event;

class Engine {
public:
	Engine();
	~Engine();

	bool loadConfig(const std::string& file);

	int execute();

private:
	void onEvent(const SDL_Event& event);

private:
	unsigned m_width;
	unsigned m_height;

	bool m_run;
	int m_returnCode;
};

#endif // ENGINE_H
