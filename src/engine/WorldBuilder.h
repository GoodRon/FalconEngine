#ifndef WORLD_BUILDER_H
#define WORLD_BUILDER_H

#include <memory>
#include <string>
#include <map>

class ResourceManager;
class Unit;
// class UnitBuilder;
class IAnimation;

namespace engine {
	class WorldBuilder {
	public:
		WorldBuilder(ResourceManager* resourceManager);

		~WorldBuilder();

		std::shared_ptr<Unit> buildUnit(const std::string& jsonRecipe);

	private:
		IAnimation* loadAnimation(const std::string& json);

	private:
		ResourceManager* m_resourceManager;
		// std::map<std::string, UnitBuilder*> m_unitBuilders;
	}
}

#endif // WORLD_BUILDER_H