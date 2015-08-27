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
		cerr << "Unable to load image " << name << ". Error: " << IMG_GetError()
			 << endl;
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

AnimationPointer ResourceManager::loadAnimation(const string& json) {
	AnimationPointer animationPtr;

	ifstream jsonFile;
	jsonFile.open(json);
	if (!jsonFile.good()) {
		cerr << "Can't open json file " << json << endl;
	}

	string line;
	string jsonContent;
	while (getline(jsonFile, line)) {
		jsonContent += line;
	}

	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(jsonContent, root)) {
		cerr << "Can't parse json from " << json << endl;
		return animationPtr;
	}

	auto name = root.get("name", "null").asString();

	// TODO добавить обработку "animation"
	if (root.get("type", "null").asString() != "directedAnimation") {
		cerr << "Can't create animation from " << json << endl;
		return animationPtr;
	}

	auto textureFile = root.get("texture", "null").asString();
	auto texture = loadTexture(textureFile);

	if (!texture) {
		cerr << "Can't create animation from " << json << " '" << textureFile << "'" << endl;
		return animationPtr;
	}

	// TODO сделать загрузку отдельными фреймами, а не целыми линиями
	auto width = root.get("width", 0).asInt();
	auto height = root.get("height", 0).asInt();
	auto cols = root.get("cols", 0).asInt();
	auto rows = root.get("rows", 0).asInt();
	auto scale = root.get("scale", 0).asInt();
	chrono::milliseconds period(root.get("periodMs", 0).asInt());

	if ((width <= 0) || (height <= 0) || (cols <= 0) || (rows <= 0)) {
		cerr << "Can't create animation from " << json << endl;
		return animationPtr;
	}

	Uint32 format;
	int access, textureWidth, textureHeight;
	SDL_QueryTexture(texture.get(), &format, &access, &textureWidth, &textureHeight);
	vector<pair<double, Animation>> animations;

	// TODO make it better
	Json::Value animationSets = root["animations"];
	for (int index = 0; static_cast<size_t>(index) < animationSets.size(); ++index) {
		auto direction = animationSets[index].get("direction", 0.0).asDouble();
		auto row = animationSets[index].get("row", 0).asInt();

		vector<TexturePointer> frames;
		for (int col = 0; col < cols; ++col) {
			stringstream stream;
			stream << textureFile << "_w" << width << "_h" << height
				   << "_c" << col << "_r" << row;
			string cachedFrameName;
			stream >> cachedFrameName;

			if (m_textureCache.find(cachedFrameName) != m_textureCache.end()) {
				frames.push_back(m_textureCache.at(cachedFrameName));
				continue;
			}

			TexturePointer frame(SDL_CreateTexture(m_renderer->getContext(),
												  format, SDL_TEXTUREACCESS_TARGET,
												  width * scale, height * scale),
								 SDL_DestroyTexture);
			SDL_Rect crop = {static_cast<int>(col * width),
							 static_cast<int>(row * height),
							 width, height};
			m_renderer->clearTexture(frame);
			m_renderer->drawTextureToTexture(texture, frame, &crop, nullptr);
			m_textureCache.emplace(cachedFrameName, frame);
			frames.push_back(frame);
		}

		Animation animation(frames, period);
		animations.emplace_back(direction, animation);
	}

	animationPtr.reset(dynamic_cast<IAnimation*>(new DirectedAnimation(animations)));
	return animationPtr;
}

void ResourceManager::freeUnused() {
	for (auto texture = m_textureCache.begin(); texture != m_textureCache.end(); ++texture) {
		if ((*texture).second.use_count() <= 1) {
			m_textureCache.erase(texture);
		}
	}
}
