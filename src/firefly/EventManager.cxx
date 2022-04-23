#include "EventManager.h"

#include "SystemManager.h"
#include "StateMachine.h"

#include "events/IEvent.h"

namespace firefly {

EventManager::EventManager(
	StateMachine* stateMachine,
	SystemManager* systemManager):
	_stateMachine(stateMachine),
	_systemManager(systemManager),
	_hasNewEvents(false),
	_queueMutex(),
	_events() {
}

EventManager::~EventManager() {
}

bool EventManager::registerEvent(
	const std::shared_ptr<IEvent>& event) {

	constexpr size_t maxEvents = 1024;

	std::lock_guard<std::mutex> lock(_queueMutex);
	if (_events.size() > maxEvents) {
		return false;
	}

	_events.push(event);
	_hasNewEvents = true;
	return true;
}

void EventManager::processEvents() {
	if (!_hasNewEvents) {
		return;
	}

	std::queue<std::shared_ptr<IEvent>> events;

	_queueMutex.lock();
	events.swap(_events);
	_hasNewEvents = false;
	_queueMutex.unlock();

	bool isHandled = false;
	while (!events.empty()) {
		isHandled = _stateMachine->processEvent(events.front());

		if (!isHandled) {
			isHandled = _systemManager->processEvent(events.front());
		}
		events.pop();
	}
}

}
