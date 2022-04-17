/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_IANIMATION_H
#define FALCON_IANIMATION_H

#include <memory>

struct SDL_Texture;

namespace falcon {

using TexturePointer = std::shared_ptr<SDL_Texture>;

class IAnimation {
public:
	IAnimation() {}

	virtual ~IAnimation() {}

	virtual void play() = 0;

	virtual void pause() = 0;

	virtual bool isPaused() = 0;

	virtual void setLoop(bool isLooped) = 0;

	virtual bool isLooped() const = 0;

	virtual TexturePointer getFrame() = 0;

	virtual TexturePointer getFrame(double direction) {
		direction = direction;
		return getFrame();
	}
};

}

#endif // FALCON_IANIMATION_H
