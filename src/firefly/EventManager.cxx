#include "EventManager.h"

#include "SystemManager.h"
#include "events/IEvent.h"

namespace firefly {

// TODO extend it
// TODO add multithread protection

EventManager::EventManager(SystemManager* systemManager):
	_systemManager(systemManager) {
}

EventManager::~EventManager() {
}

void EventManager::sendEvent(
	const std::shared_ptr<IEvent>& event) const {

	_systemManager->onEvent(event);
}

}
