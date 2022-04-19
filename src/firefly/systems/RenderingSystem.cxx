#include "RenderingSystem.h"

#include "Entity.h"
#include "Engine.h"
#include "Frame.h"
#include "Renderer.h"

#include "components/Visual.h"
#include "components/Position.h"

namespace firefly {

RenderingSystem::RenderingSystem(Engine* engine):
	ISystem("RenderingSystem", engine),
	_entityMutex(),
	_renderer(engine->getRenderer()) {

	_requiredComponents.push_front(Visual::ComponentName);
	_requiredComponents.push_front(Position::ComponentName);
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
			entity.second->getComponent(
				getComponentId(Position::ComponentName)));

		auto visualComponent = static_cast<Visual*>(
			entity.second->getComponent(
				getComponentId(Visual::ComponentName)));

		draw(positionComponent, visualComponent);
	}

	unlockEntities();
}

bool RenderingSystem::onEvent(
    const std::shared_ptr<IEvent>& event) {

	// TODO write me
	return false;
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
	SDL_Point center = positionComponent->center();

	_renderer->drawTexture(frame->getTexture(), &source, &dest, 
		positionComponent->angle, &center);
}

}