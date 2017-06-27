/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <jsoncpp/json/json.h>

#include "ResourceManager.h"
#include "Renderer.h"
#include "Animation.h"
#include "DirectedAnimation.h"
#include "helpers.h"

using namespace std;

ResourceManager::ResourceManager(Renderer* renderer) :
m_renderer(renderer) {
}

ResourceManager::~ResourceManager() {
}

TexturePointer ResourceManager::loadTexture(const string& name) {
	if (m_textureCache.find(name) != m_textureCache.end()) {
		return m_textureCache.at(name);
	}

	TexturePointer ptr;
	if (!m_renderer) {
		return ptr;
	}

	SDL_Surface* surface = IMG_Load(name.c_str());
	if (surface == nullptr) {
		cerr << "Unable to load image " << name << ". Error: " 
			 << IMG_GetError() << endl;
		return ptr;
	}

	auto texture = SDL_CreateTextureFromSurface(m_renderer->getContext(),
												surface);
	if (texture == nullptr) {
		cerr << "Unable to create texture from image " << name << ". Error: "
			 << SDL_GetError() << endl;
		SDL_FreeSurface(surface);
		return ptr;
	}

	SDL_FreeSurface(surface);
	ptr.reset(texture, SDL_DestroyTexture);
	m_textureCache.emplace(name, ptr);
	return ptr;
}

TexturePointer ResourceManager::frameFromTexture(const std::string& 
	textureName, SDL_Rect rect, int scale) {
	stringstream stream;
	string cachedFrameName;

	stream << textureName << "_w" << rect.w << "_h" << rect.h
	   	   << "_x" << rect.x << "_y" << rect.y << "_s" << scale;
	stream >> cachedFrameName;

	if (m_textureCache.find(cachedFrameName) != m_textureCache.end()) {
		return m_textureCache.at(cachedFrameName);
	}

	auto texture = loadTexture(textureName);

	if (!texture) {
		cerr << "Can't create frame from " << textureName << endl;
		return TexturePointer();
	}

	Uint32 format;
	int access, textureWidth, textureHeight;
	SDL_QueryTexture(texture.get(), &format, &access, 
					 &textureWidth, &textureHeight);

	TexturePointer frame(SDL_CreateTexture(m_renderer->getContext(),
						 format, SDL_TEXTUREACCESS_TARGET, 
						 rect.w * scale, rect.h * scale),
						 SDL_DestroyTexture);

	m_renderer->clearTexture(frame);
	m_renderer->drawTextureToTexture(texture, frame, &rect, nullptr);
	m_textureCache.emplace(cachedFrameName, frame);
	return frame;
}

AnimationArray ResourceManager::loadAnimation(const string& json) {
	AnimationArray array;

	auto content = engine::helpers::readFile(json);

	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(content, root)) {
		cerr << "Can't parse json from " << json << endl;
		return array;
	}

	auto name = root.get("name", "").asString();
	auto textureFile = root.get("texture", "").asString();
	auto texture = loadTexture(textureFile);

	if (!texture) {
		cerr << "Can't create animation from " << json << " '" 
			 << textureFile << "'" << endl;
		return array;
	}

	// TODO сделать загрузку отдельными фреймами, а не целыми линиями
	auto width = root.get("width", 0).asInt();
	auto height = root.get("height", 0).asInt();
	auto cols = root.get("cols", 0).asInt();
	auto rows = root.get("rows", 0).asInt();
	auto scale = root.get("scale", 0).asInt();
	chrono::milliseconds period(root.get("period_ms", 0).asInt());

	if ((width <= 0) || (height <= 0) || (cols <= 0) || (rows <= 0)) {
		cerr << "Can't create animation from " << json << endl;
		return array;
	}

	// TODO make it better
	Json::Value animationSet = root["frames"];
	for (size_t index = 0; index < animationSet.size(); ++index) {
		auto direction = animationSet[index].get("direction", 0.0).asDouble();
		auto row = animationSet[index].get("row", 0).asInt();

		vector<TexturePointer> frames;
		for (int col = 0; col < cols; ++col) {
			SDL_Rect rect = {col * width, row * height, width, height};
			auto frame = frameFromTexture(textureFile, rect, scale);
			frames.push_back(frame);
		}

		AnimationPointer animation(new Animation(frames, period));
		dynamic_pointer_cast<Animation>(animation)->setDirection(direction);
		array.push_back(animation);
	}
	return array;
}

void ResourceManager::freeUnused() {
	for (auto texture = m_textureCache.begin(); texture != m_textureCache.end(); 
		++texture) {
		if ((*texture).second.use_count() <= 1) {
			m_textureCache.erase(texture);
		}
	}
}
