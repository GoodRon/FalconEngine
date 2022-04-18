#include "RenderingSystem.h"

#include "Entity.h"
#include "Engine.h"
#include "Frame.h"
#include "Renderer.h"

#include "components/Visual.h"
#include "components/Position.h"

namespace firefly {

RenderingSystem::RenderingSystem(Engine* engine):
	ISystem("Rendering", engine),
	_visualComponentId(getComponentId(Visual::ComponentName)),
	_positionComponentId(getComponentId(Position::ComponentName)),
	_entityMutex(),
	_renderer(engine->getRenderer()) {
}

RenderingSystem::~RenderingSystem() {
}

void RenderingSystem::drawEntites() const {
	// TODO improve
	lockEntities();

	Position* positionComponent = nullptr;
	Visual* visualComponent = nullptr;
	
	for (auto& entity: _entities) {
		auto positionComponent = static_cast<Position*>(
			entity.second->getComponent(_positionComponentId));

		auto visualComponent = static_cast<Visual*>(
			entity.second->getComponent(_visualComponentId));

		draw(positionComponent, visualComponent);
	}

	unlockEntities();
}

bool RenderingSystem::onEvent(
    const std::shared_ptr<IEvent>& event) const {

	// TODO write me
	return true;
}

bool RenderingSystem::checkComponents(Entity* entity) const {
	if (!entity) {
		return false;
	}

	auto component = entity->getComponent(_visualComponentId);
	if (!component) {
		return false;
	}

	component = entity->getComponent(_positionComponentId);
	if (!component) {
		return false;
	}
	return true;
}

void RenderingSystem::lockEntities() const {
	_entityMutex.lock();
}

void RenderingSystem::unlockEntities() const {
	_entityMutex.unlock();
}

void RenderingSystem::draw(Position* positionComponent, 
        Visual* visualComponent) const {
	if (!positionComponent || !visualComponent) {
		return;
	}

	Visual::State& state = visualComponent->states[visualComponent->currentState];
	auto& frames = state.frames[visualComponent->currentDirection];
	if (frames.empty()) {
		return;
	}

	// TODO check index
	auto frame = frames[visualComponent->frameIndex];

	// TODO improve
	SDL_Rect source = frame->getSourceRect();
	SDL_Rect dest = positionComponent->toRect();
	_renderer->drawTexture(frame->getTexture(), &source, &dest);
}

}