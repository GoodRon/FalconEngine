/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNITCONTEXT_H
#define UNITCONTEXT_H

#include <memory>

class UnitState;
class WorldObject;
struct SDL_Texture;

/**
 * @brief Умный указатель на объект текстуры
 */
typedef std::shared_ptr<SDL_Texture> TexturePointer;

class UnitContext {
public:
	UnitContext();
	virtual ~UnitContext();

	void moveTo(int x, int y);

	void stop();

	TexturePointer getFrame();

private:
	UnitState* m_state;
};

#endif // UNITCONTEXT_H
