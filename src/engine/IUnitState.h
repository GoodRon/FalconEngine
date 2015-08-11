/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef IUNITSTATE_H
#define IUNITSTATE_H

#include <memory>

class UnitContext;
struct SDL_Texture;

/**
 * @brief Умный указатель на объект текстуры
 */
typedef std::shared_ptr<SDL_Texture> TexturePointer;

class IUnitState {
	virtual ~IUnitState() = 0;

	virtual void moveTo(int x, int y, UnitContext*
						context) = 0;

	virtual void stop(UnitContext* context) = 0;

	virtual TexturePointer getFrame() = 0;
};

#endif // IUNITSTATE_H
