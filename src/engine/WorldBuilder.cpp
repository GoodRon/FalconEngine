#include "WorldBuilder.h"
#include "ResourceManager.h"
#include "Unit.h"
#include "IAnimation.h"
#include "DirectedAnimation.h"

engine::WorldBuilder::WorldBuilder(ResourceManager* resourceManager) :
	m_resourceManager(resourceManager),
	m_unitBuilders() {
}

engine::WorldBuilder::~WorldBuilder() {
	for (auto& builder: m_unitBuilders) {
		delete builder.second;
	}
}

std::shared_ptr<Unit> engine::WorldBuilder::buildUnit
	(const std::string& jsonRecipe) {
	
}

IAnimation* engine::WorldBuilder::
loadAnimation(const std::string& json) {

}
