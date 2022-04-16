#include "Frame.h"

namespace falcon {

Frame::Frame(const TexturePointer& texture, 
	const SDL_Rect& sourceRect): 
	_texture(texture),
	_sourceRect(sourceRect) {
}

Frame::~Frame() {
}

TexturePointer Frame::getTexture() const {
	return _texture;
}

SDL_Rect Frame::getSourceRect() const {
	return _sourceRect;
}

}
