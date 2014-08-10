/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Tile.h"

Tile::Tile(TexturePointer& texture) :
    m_texture(texture),
    m_x(0),
    m_y(0),
    m_width(0),
    m_height(0),
    m_visible(false) {
}

TexturePointer Tile::getTexture() const {
    return m_texture;
}

void Tile::setPosition(int x, int y) {
    m_x = x;
    m_y = y;
}

SDL_Rect Tile::getPositionAndProfile() const {
    SDL_Rect rect = {m_x, m_y, m_width, m_height};
    SDL_QueryTexture(m_texture.get(), nullptr, nullptr, &(rect.w), &(rect.h));
    return rect;
}

void Tile::setVisible(bool visible) {
    m_visible = visible;
}

bool Tile::isVisible() const {
    return m_visible;
}
