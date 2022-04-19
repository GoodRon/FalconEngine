#include "EntityBuilder.h"

#include <functional>
#include <unordered_map>
#include <fstream>

#include "firefly/Engine.h"
#include "firefly/ResourceManager.h"
#include "firefly/Entity.h"
#include "firefly/Frame.h"
#include "firefly/GameObject.h"

#include "firefly/components/Visual.h"
#include "firefly/components/Position.h"
#include "firefly/components/Velocity.h"
#include "firefly/components/Player.h"
#include "firefly/components/Solidity.h"

#include "rapidjson/document.h"

namespace spacewar {

class EntityBuilder::Impl {
private:
	using componentBuilder = std::function<bool(
		firefly::Entity* entity,
		rapidjson::Value& document)>;

	firefly::Engine* const _engine;
	std::unordered_map<std::string, componentBuilder> _componentBuilders;

public:

	Impl(firefly::Engine* engine):
		_engine(engine),
		_componentBuilders() {

		registerComponentBuilders();
	}

	~Impl() {
	}

	Impl(const Impl&) = delete;
	Impl& operator=(const Impl&) = delete;

	std::shared_ptr<firefly::Entity> buildEntity(
		const std::string& jsonConfig) {
		if (!_engine) {
			return nullptr;
		}

		// TODO check if the document is a valid json

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

		auto entityName = std::string(document["name"].GetString());

		std::shared_ptr<firefly::Entity> entity(new firefly::Entity(entityName));

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
		_componentBuilders[firefly::Visual::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildVisualComponent(entity, document);
		};

		_componentBuilders[firefly::Position::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildPositionComponent(entity, document);
		};

		_componentBuilders[firefly::Velocity::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildVelocityComponent(entity, document);
		};

		_componentBuilders[firefly::Player::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildPlayerComponent(entity, document);
		};

		_componentBuilders[firefly::Solidity::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildSolidityComponent(entity, document);
		};
	}

	// TODO move to a separate functions
	bool buildVisualComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		if (!entity) {
			return false;
		}

		auto resourceManager = _engine->getResourceManager();
		if (!resourceManager) {
			return false;
		}

		std::unique_ptr<firefly::Visual> component(new firefly::Visual);
		component->zIndex = document["zIndex"].GetInt();

		for (auto& state: document["states"].GetArray()) {
			const auto stateName = std::string(state["name"].GetString());
			const auto texturePath = std::string(state["texture"].GetString());

			const auto texture = resourceManager->loadTexture(texturePath);
			if (!texture) {
				// TODO log error
				return false;
			}

			SDL_Rect frameRect;
			frameRect.w = state["frameWidth"].GetInt();
			frameRect.h = state["frameHeight"].GetInt();
			int duration = state["frameDuration"].GetInt();

			firefly::Visual::State visualState;
			visualState.isLooped = state["isLooped"].GetBool();

			for (auto& frameLine: state["frames"].GetArray()) {
				const int direction = frameLine["direction"].GetInt();
				const int row = frameLine["row"].GetInt();
				const int col = frameLine["col"].GetInt();
				const int amount = frameLine["amount"].GetInt();

				firefly::Visual::Frames frames;

				frameRect.y = row * frameRect.h;
				for (int frameCount = 0; frameCount < amount; ++frameCount) {
					frameRect.x = (col + frameCount) * frameRect.w;
					
					frames.emplace_back(
						new firefly::Frame(texture, frameRect, duration));
				}

				visualState.frames[direction] = std::move(frames);
			}

			component->states[stateName] = std::move(visualState);
		}

		entity->addComponent(std::move(component));
		return true;
	}

	bool buildPositionComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Position> component(new firefly::Position);

		component->x = document["x"].GetDouble();
		component->y = document["y"].GetDouble();
		component->centerX = document["centerX"].GetDouble();
		component->centerY = document["centerY"].GetDouble();
		component->width = document["width"].GetDouble();
		component->height = document["height"].GetDouble();
		component->scale = document["scale"].GetDouble();
		component->angle = document["angle"].GetDouble();

		entity->addComponent(std::move(component));
		return true;
	}

	bool buildVelocityComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Velocity> component(new firefly::Velocity);

		component->speed = document["speed"].GetDouble();
		component->speedAngle = document["speedAngle"].GetDouble();
		component->maxSpeed = document["maxSpeed"].GetDouble();
		component->acceleration = document["acceleration"].GetDouble();
		component->accelerationAngle = document["accelerationAngle"].GetDouble();

		entity->addComponent(std::move(component));
		return true;
	}

	bool buildPlayerComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Player> component(new firefly::Player);

		component->playerId = document["playerId"].GetInt();

		entity->addComponent(std::move(component));
		return true;
	}

	bool buildSolidityComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Solidity> component(new firefly::Solidity);

		component->isSolid = document["isSolid"].GetBool();
		component->isDestructable = document["isDestructable"].GetBool();
		component->hasGravity = document["hasGravity"].GetBool();
		component->mass = document["mass"].GetDouble();

		entity->addComponent(std::move(component));
		return true;
	}
};

EntityBuilder::EntityBuilder(firefly::Engine* engine):
	_impl(new Impl(engine)) {
}

EntityBuilder::~EntityBuilder() {
}

std::shared_ptr<firefly::Entity> 
EntityBuilder::buildEntity(const std::string& jsonConfig) {
	return _impl->buildEntity(jsonConfig);
}

}

