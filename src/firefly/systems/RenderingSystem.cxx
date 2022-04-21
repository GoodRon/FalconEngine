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

	auto frame = state.frames[visualComponent->frameIndex];
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
		}
	}

	frame = state.frames[visualComponent->frameIndex];
	return frame.get();
}

RenderingSystem::RenderingSystem(Engine* engine):
	ISystem("RenderingSystem", engine),
	_mutex(),
	_renderer(engine->getRenderer()),
	_isRenderListChanged(false),
	_renderList() {

	_requiredComponents.push_front(Visual::ComponentName);
	_requiredComponents.push_front(Position::ComponentName);
}

RenderingSystem::~RenderingSystem() {
}

void RenderingSystem::drawEntites() {
	if (_isRenderListChanged) {
		_renderList.clear();

		lockEntities();
		_renderList.reserve(_entities.size());

		for (auto& entity: _entities) {
			_renderList.push_back(entity.second);
		}

		_isRenderListChanged = false;
		unlockEntities();

		std::sort(_renderList.begin(), _renderList.end(), sortEntities);
	}

	const uint64_t timepoint = SDL_GetTicks64();
	Position* positionComponent = nullptr;
	Visual* visualComponent = nullptr;

	for (auto& entity: _renderList) {
		positionComponent = entity->getComponent<Position>();
		visualComponent = entity->getComponent<Visual>();

		if (!visualComponent->isVisible) {
			continue;
		}

		draw(positionComponent, visualComponent, timepoint);
	}
}

void RenderingSystem::lockEntities() const {
	_mutex.lock();
}

void RenderingSystem::unlockEntities() const {
	_mutex.unlock();
}

void RenderingSystem::onRegisterEntity(Entity* entity) {
	_isRenderListChanged = true;
}

void RenderingSystem::onUnregisterEntity(Entity* entity) {
	_isRenderListChanged = true;
}

void RenderingSystem::draw(Position* positionComponent, 
		Visual* visualComponent, uint64_t timepoint) const {
	if (!positionComponent || !visualComponent) {
		return;
	}

	const auto frame = advanceFrame(visualComponent, timepoint);
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