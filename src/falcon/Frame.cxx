#include "Frame.h"

namespace falcon {

Frame::Frame(const TexturePointer& texture, 
	const SDL_Rect& sourceRect,
	int durationMs): 
	_texture(texture),
	_sourceRect(sourceRect),
	_durationMs(durationMs) {
}

Frame::~Frame() {
}

TexturePointer Frame::getTexture() const {
	return _texture;
}

SDL_Rect Frame::getSourceRect() const {
	return _sourceRect;
}

int Frame::getDuration() const {
	return _durationMs;
}

}
