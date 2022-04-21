#include "RenderingSystem.h"

#include <algorithm>

#include <SDL_timer.h>

#include "Entity.h"
#include "Engine.h"
#include "Frame.h"
#include "Renderer.h"

#include "components/Visual.h"
#include "components/Position.h"

namespace firefly {

static bool sortEntities(Entity* lhs, Entity* rhs) {
	if (!lhs || !rhs) {
		return true;
	}

	const auto visualComponentLhs = lhs->getComponent<Visual>();
	const auto visualComponentRhs = rhs->getComponent<Visual>();

	if (!visualComponentLhs || !visualComponentRhs) {
		return true;
	}
	return visualComponentLhs->zIndex < visualComponentRhs->zIndex;
}

static Frame* advanceFrame(Visual* visualComponent, uint64_t timepoint) {
	if (!visualComponent) {
		return nullptr;
	}

	if (visualComponent->states.find(visualComponent->currentState) == 
		visualComponent->states.end()) {
		return nullptr;
	}

	auto& state = visualComponent->states[visualComponent->currentState];
	if (state.frames.empty()) {
		return nullptr;
	}

	if (visualComponent->frameIndex >= state.frames.size()) {
		visualComponent->frameIndex = 0;
	}

	auto& frame = state.frames[visualComponent->frameIndex];
	const auto duration = frame->getDuration();

	if (duration == 0 || timepoint < visualComponent->timepoint) {
		return frame.get();
	}

	const uint64_t elapsedMs = timepoint - visualComponent->timepoint;
	if (elapsedMs < duration) {
		return frame.get();
	}

	visualComponent->timepoint = timepoint + duration - elapsedMs;

	visualComponent->frameIndex++;
	if (visualComponent->frameIndex >= state.frames.size()) {
		if (state.isLooped) {
			visualComponent->frameIndex = 0;
		} else {
			visualComponent->frameIndex--;
			state.isStopped = true;
		}
	}

	frame = state.frames[visualComponent->frameIndex];
	return frame.get();
}

RenderingSystem::RenderingSystem(Engine* engine):
	ISystem("RenderingSystem", engine),
	_renderer(engine->getRenderer()) {

	addRequiredComponent(Visual::ComponentName);
	addRequiredComponent(Position::ComponentName);
}

RenderingSystem::~RenderingSystem() {
}

void RenderingSystem::onUpdate() {

	Position* positionComponent = nullptr;
	Visual* visualComponent = nullptr;

	_renderer->clearViewport();

	for (auto& entity: getEntities()) {
		positionComponent = entity.second->getComponent<Position>();
		visualComponent = entity.second->getComponent<Visual>();

		if (!visualComponent->isVisible) {
			continue;
		}

		draw(positionComponent, visualComponent);
	}
	
	SDL_RenderPresent(_renderer->getContext());
}

void RenderingSystem::draw(Position* positionComponent, 
		Visual* visualComponent) const {
	if (!positionComponent || !visualComponent) {
		return;
	}

	const auto frame = advanceFrame(visualComponent, getLastUpdateTimepoint());
	if (!frame) {
		return;
	}

	// TODO improve
	SDL_Rect source = frame->getSourceRect();
	SDL_Rect dest = positionComponent->toRect();
	SDL_Point center = positionComponent->center();

	_renderer->drawTexture(frame->getTexture(), &source, &dest, 
		positionComponent->angle, &center);
}

}