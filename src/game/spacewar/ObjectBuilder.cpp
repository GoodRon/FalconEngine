#include "ObjectBuilder.h"

#include <functional>
#include <unordered_map>
#include <fstream>

#include "falcon/Engine.h"
#include "falcon/ResourceManager.h"
#include "falcon/ComponentRegistry.h"
#include "falcon/Entity.h"
#include "falcon/GameObject.h"

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

	std::shared_ptr<falcon::IGameObject> buildShip(
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

		auto entityName = std::string(document["name"].GetString());

		std::shared_ptr<falcon::Entity> entity(new falcon::Entity(entityName));

		for (auto& component: document["components"].GetArray()) {
			auto componentName = std::string(component["name"].GetString());

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

		auto componentRegistry = _engine->getComponentRegistry();
		auto resourceManager = _engine->getResourceManager();

		if (!resourceManager || !componentRegistry) {
			return false;
		}

		auto visualId = componentRegistry->findComponentID("Visual");
		if (visualId < 0) {
			return false;
		}

		//auto visualComponent = componentRegistry->makeComponent(visualId);

		return true;
	}
};

ObjectBuilder::ObjectBuilder(falcon::Engine* engine):
	_impl(new Impl(engine)) {
}

ObjectBuilder::~ObjectBuilder() {
}

std::shared_ptr<falcon::IGameObject> 
ObjectBuilder::buildShip(const std::string& jsonConfig) {
	return _impl->buildShip(jsonConfig);
}

}

