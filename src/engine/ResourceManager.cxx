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

namespace falcon {

ResourceManager::ResourceManager(Renderer* renderer) :
	_renderer(renderer),
	_textureCache() {
}

ResourceManager::~ResourceManager() {
}

TexturePointer ResourceManager::loadTexture(const std::string& name) {
	if (_textureCache.find(name) != _textureCache.end()) {
		return _textureCache.at(name);
	}

	if (!_renderer) {
		return nullptr;
	}

	SDL_Surface* surface = IMG_Load(name.c_str());
	if (surface == nullptr) {
		//cerr << "Unable to load image " << name << ". Error: " << IMG_GetError()
		//	 << endl;
		return nullptr;
	}

	auto texture = SDL_CreateTextureFromSurface(_renderer->getContext(),
												surface);
	if (texture == nullptr) {
		//cerr << "Unable to create texture from image " << name << ". Error: "
		//	 << SDL_GetError() << endl;
		SDL_FreeSurface(surface);
		return nullptr;
	}

	SDL_FreeSurface(surface);

	TexturePointer ptr(texture, SDL_DestroyTexture);
	_textureCache.emplace(name, ptr);
	return ptr;
}

AnimationPointer ResourceManager::loadAnimation(const std::string& json) {
	std::ifstream jsonFile;
	jsonFile.open(json);
	if (!jsonFile.good()) {
		//cerr << "Can't open json file " << json << endl;
		return nullptr;
	}

	std::string line;
	std::string jsonContent;
	while (getline(jsonFile, line)) {
		jsonContent += line;
	}

	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(jsonContent, root)) {
		//cerr << "Can't parse json from " << json << endl;
		return nullptr;
	}

	auto name = root.get("name", "null").asString();

	if (root.get("type", "null").asString() != "directedAnimation") {
		//cerr << "Can't create animation from " << json << endl;
		return nullptr;
	}

	auto textureFile = root.get("texture", "null").asString();
	auto texture = loadTexture(textureFile);

	if (!texture) {
		//cerr << "Can't create animation from " << json << " '" << textureFile << "'" << endl;
		return nullptr;
	}

	auto width = root.get("width", 0).asInt();
	auto height = root.get("height", 0).asInt();
	auto cols = root.get("cols", 0).asInt();
	auto rows = root.get("rows", 0).asInt();
	auto scale = root.get("scale", 0).asInt();
	std::chrono::milliseconds period(root.get("periodMs", 0).asInt());

	if ((width <= 0) || (height <= 0) || (cols <= 0) || (rows <= 0)) {
		//cerr << "Can't create animation from " << json << endl;
		return nullptr;
	}

	Uint32 format;
	int access, textureWidth, textureHeight;
	SDL_QueryTexture(texture.get(), &format, &access, &textureWidth, &textureHeight);
	std::vector<std::pair<double, Animation>> animations;

	// TODO make it better
	Json::Value animationSets = root["animations"];
	for (int index = 0; index < static_cast<int>(animationSets.size()); ++index) {
		auto direction = animationSets[index].get("direction", 0.0).asDouble();
		auto row = animationSets[index].get("row", 0).asInt();

		std::vector<TexturePointer> frames;
		for (int col = 0; col < cols; ++col) {
			std::stringstream stream;
			stream << textureFile << "_w" << width << "_h" << height
				   << "_c" << col << "_r" << row;
			std::string cachedFrameName;
			stream >> cachedFrameName;

			if (_textureCache.find(cachedFrameName) != _textureCache.end()) {
				frames.push_back(_textureCache.at(cachedFrameName));
				continue;
			}

			TexturePointer frame(SDL_CreateTexture(_renderer->getContext(),
												  format, SDL_TEXTUREACCESS_TARGET,
												  width * scale, height * scale),
								 SDL_DestroyTexture);
			SDL_Rect crop = {static_cast<int>(col * width),
							 static_cast<int>(row * height),
							 width, height};
			_renderer->clearTexture(frame);
			_renderer->drawTextureToTexture(texture, frame, &crop, nullptr);
			_textureCache.emplace(cachedFrameName, frame);
			frames.push_back(frame);
		}

		Animation animation(frames, period);
		animations.emplace_back(direction, std::move(animation));
	}

	AnimationPointer animationPtr(new DirectedAnimation(animations));
	return animationPtr;
}

void ResourceManager::freeUnused() {
	for (auto texture = _textureCache.begin(); texture != _textureCache.end(); ++texture) {
		if ((*texture).second.use_count() <= 1) {
			_textureCache.erase(texture);
		}
	}
}

}
