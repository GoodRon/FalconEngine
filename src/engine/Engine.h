#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include <SDL2/SDL.h>

class Engine {
public:
	Engine(int argc, char** argv);
	~Engine();

	bool loadConfig(const std::string& file) {}

	int execute();

private:
	bool init();
	void onEvent(const SDL_Event& event) {}

private:
	unsigned m_width;
	unsigned m_height;

	bool m_run;
	int m_returnCode;
};

#endif // ENGINE_H
