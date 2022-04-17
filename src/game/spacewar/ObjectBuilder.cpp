#include "ObjectBuilder.h"

#include <functional>
#include <unordered_map>
#include <fstream>

#include "falcon/Engine.h"
#include "falcon/ResourceManager.h"
#include "falcon/Entity.h"
#include "falcon/Frame.h"
#include "falcon/GameObject.h"
#include "falcon/components/Visual.h"

#include "rapidjson/document.h"

namespace spacewar {

class ObjectBuilder::Impl {
private:
	using componentBuilder = std::function<void(
		falcon::Entity* entity,
		rapidjson::Value& document)>;

	falcon::Engine* const _engine;
	std::unordered_map<std::string, componentBuilder> _componentBuilders;

public:

	Impl(falcon::Engine* engine):
		_engine(engine),
		_componentBuilders() {

		_componentBuilders["Visual"] = [this](
			falcon::Entity* entity,
			rapidjson::Value& document) {
			buildVisualComponent(entity, document);
		};	
	}

	~Impl() {
	}

	Impl(const Impl&) = delete;
	Impl& operator=(const Impl&) = delete;

	std::shared_ptr<falcon::IGameObject> buildObject(
		const std::string& jsonConfig) {
		if (!_engine) {
			return nullptr;
		}

		std::ifstream jsonFile;
		jsonFile.open(jsonConfig);
		if (!jsonFile.good()) {
			return nullptr;
		}

		std::string line;
		std::string jsonContent;
		while (getline(jsonFile, line)) {
			jsonContent += line;
		}

		rapidjson::Document document;
		document.Parse(jsonContent.c_str());

		const auto entityName = std::string(document["name"].GetString());

		std::shared_ptr<falcon::Entity> entity(new falcon::Entity(entityName));

		for (auto& component: document["components"].GetArray()) {
			const auto componentName = std::string(component["name"].GetString());

			if (_componentBuilders.find(componentName) == _componentBuilders.end()) {
				// TODO notify about error
				continue;
			}

			// TODO check result
			_componentBuilders[componentName](entity.get(), component);
		}

		return std::shared_ptr<falcon::IGameObject>();
	}


private:
	bool buildVisualComponent(
		falcon::Entity* entity,
		rapidjson::Value& document) const {

		auto resourceManager = _engine->getResourceManager();
		if (!resourceManager) {
			return false;
		}

		std::unique_ptr<falcon::Visual> component(new falcon::Visual);

		for (auto& state: document["states"].GetArray()) {
			const auto stateName = std::string(state["name"].GetString());
			const auto texturePath = std::string(state["texture"].GetString());

			const auto texture = resourceManager->loadTexture(texturePath);
			if (!texture) {
				// TODO log error
				return false;
			}

			SDL_Rect frameRect;
			frameRect.w = state["frame_width"].GetInt();
			frameRect.h = state["frame_height"].GetInt();

			falcon::Visual::AnimatedState animatedState;

			for (auto& direction: document["directions"].GetArray()) {
				const int directionAngle = state["direction"].GetInt();
				const int row = state["row"].GetInt();
				const int col = state["col"].GetInt();
				const int framesSize = state["frames"].GetInt();

				falcon::Visual::Frames frames;

				for (int i = 0; i < framesSize; ++i) {
					frameRect.x = col * frameRect.w;
					frameRect.y = row * frameRect.h;
					frames.emplace_back(new falcon::Frame(texture, frameRect));
				}

				animatedState[directionAngle] = std::move(frames);
			}

			component->states[stateName] = std::move(animatedState);
		}

		entity->addComponent(std::move(component));
		return true;
	}
};

ObjectBuilder::ObjectBuilder(falcon::Engine* engine):
	_impl(new Impl(engine)) {
}

ObjectBuilder::~ObjectBuilder() {
}

std::shared_ptr<falcon::IGameObject> 
ObjectBuilder::buildObject(const std::string& jsonConfig) {
	return _impl->buildObject(jsonConfig);
}

}

