/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>

#include "rapidjson/document.h"

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

	rapidjson::Document document;

	document.Parse(jsonContent.c_str());

	auto name = std::string(document["name"].GetString());

	auto animationType = std::string(document["type"].GetString());
	if (animationType != "directedAnimation") {
		//cerr << "Can't create animation from " << json << endl;
		return nullptr;
	}

	auto textureFile = std::string(document["texture"].GetString());
	auto texture = loadTexture(textureFile);

	if (!texture) {
		//cerr << "Can't create animation from " << json << " '" << textureFile << "'" << endl;
		return nullptr;
	}

	auto width = document["width"].GetInt();
	auto height = document["height"].GetInt();
	auto cols = document["cols"].GetInt();
	auto rows = document["rows"].GetInt();
	auto scale = document["scale"].GetInt();
	std::chrono::milliseconds period(document["periodMs"].GetInt());

	if ((width <= 0) || (height <= 0) || (cols <= 0) || (rows <= 0)) {
		//cerr << "Can't create animation from " << json << endl;
		return nullptr;
	}

	Uint32 format;
	int access, textureWidth, textureHeight;
	SDL_QueryTexture(texture.get(), &format, &access, &textureWidth, &textureHeight);
	std::vector<std::pair<double, Animation>> animations;

	for (auto& animationSet: document["animations"].GetArray()) {
		auto direction = animationSet["direction"].GetDouble();
		auto row = animationSet["row"].GetInt();

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
			SDL_Rect crop = { static_cast<int>(col * width),
							 static_cast<int>(row * height),
							 width, height };
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
