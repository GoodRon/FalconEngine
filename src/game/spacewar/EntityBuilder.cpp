#include "EntityBuilder.h"

#include <functional>
#include <unordered_map>
#include <fstream>

#include "falcon/Engine.h"
#include "falcon/ResourceManager.h"
#include "falcon/Entity.h"
#include "falcon/Frame.h"
#include "falcon/GameObject.h"
#include "falcon/components/Visual.h"
#include "falcon/components/Position.h"

#include "rapidjson/document.h"

namespace spacewar {

class EntityBuilder::Impl {
private:
	using componentBuilder = std::function<bool(
		falcon::Entity* entity,
		rapidjson::Value& document)>;

	falcon::Engine* const _engine;
	std::unordered_map<std::string, componentBuilder> _componentBuilders;

public:

	Impl(falcon::Engine* engine):
		_engine(engine),
		_componentBuilders() {

		registerComponentBuilders();
	}

	~Impl() {
	}

	Impl(const Impl&) = delete;
	Impl& operator=(const Impl&) = delete;

	std::shared_ptr<falcon::Entity> buildEntity(
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

		return entity;
	}

private:
	void registerComponentBuilders() {
		_componentBuilders["Visual"] = [this](
			falcon::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildVisualComponent(entity, document);
		};

		_componentBuilders["Position"] = [this](
			falcon::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildPositionComponent(entity, document);
		};
	}

	bool buildVisualComponent(
		falcon::Entity* entity,
		rapidjson::Value& document) const {

		if (!entity) {
			return false;
		}

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
			int duration = state["frame_duration"].GetInt();

			falcon::Visual::State visualState;
			visualState.isLooped = state["is_looped"].GetBool();

			for (auto& frameLine: document["frames"].GetArray()) {
				const int direction = frameLine["direction"].GetInt();
				const int row = frameLine["row"].GetInt();
				const int col = frameLine["col"].GetInt();
				const int amount = frameLine["amount"].GetInt();

				falcon::Visual::Frames frames;

				frameRect.y = row * frameRect.h;
				for (int frameCount = 0; frameCount < amount; ++frameCount) {
					frameRect.x = (col + frameCount) * frameRect.w;
					
					frames.emplace_back(
						new falcon::Frame(texture, frameRect, duration));
				}

				visualState.frames[direction] = std::move(frames);
			}

			component->states[stateName] = std::move(visualState);
		}

		entity->addComponent(std::move(component));
		return true;
	}

	bool buildPositionComponent(
		falcon::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<falcon::Position> component(new falcon::Position);

		component->x = document["x"].GetInt();
		component->y = document["y"].GetInt();
		component->width = document["width"].GetInt();
		component->height = document["height"].GetInt();
		component->scale = document["scale"].GetDouble();

		entity->addComponent(std::move(component));
		return true;
	}
};

EntityBuilder::EntityBuilder(falcon::Engine* engine):
	_impl(new Impl(engine)) {
}

EntityBuilder::~EntityBuilder() {
}

std::shared_ptr<falcon::Entity> 
EntityBuilder::buildEntity(const std::string& jsonConfig) {
	return _impl->buildEntity(jsonConfig);
}

}

