#include <algorithm>

#include "TimerPool.h"

namespace firefly {

TimerPool::TimerPool():
	_timers() {
}

TimerPool::~TimerPool() {
}

TimerPool::id_t TimerPool::addTimer(
	uint32_t milliseconds, TimerHandler handler, bool oneshoot) {

	Timer* timer = new Timer(milliseconds, handler, oneshoot);
	_timers.emplace_front(timer);
	return reinterpret_cast<id_t>(timer);
}

void TimerPool::check() {
	_timers.remove_if([](TimerPointer &x) {
		if (x->_flags.deleted) {
			return true;
		}

		if (x->check()) {
			return x->_flags.oneshoot;
		}
		return false;
	});
}

bool TimerPool::getNextShootTimeInterval(struct timeval& tv) {
	if (_timers.empty()) {
		return false;
	}

	auto it = min_element(_timers.begin(), _timers.end(), 
		[](const TimerPointer& lhs, const TimerPointer& rhs) {

		return *lhs < *rhs;
	});
	std::chrono::microseconds delta = 
		std::chrono::duration_cast<std::chrono::microseconds>(
			(*it)->_nextShoot - std::chrono::steady_clock::now());

	if (delta.count() <= 0) {
		tv.tv_sec = 0;
		tv.tv_usec = 0;
	} else {
		tv.tv_sec = delta.count() / 1000000;
		tv.tv_usec = delta.count() % 1000000;
	}
	return true;
}

void TimerPool::deleteTimer(id_t id) {
	for (auto& x: _timers) {
		if (reinterpret_cast<id_t>(x.get()) == id ) {
			x->_flags.deleted = true;
		}
	}
}

TimerPool::Timer::Timer(
	uint32_t millisec, TimerPool::TimerHandler handler, bool oneshoot):
	_interval(millisec),
	_handler(handler),
	_nextShoot(std::chrono::steady_clock::now() + _interval),
	_flags({oneshoot, false}) {
}

bool TimerPool::Timer::check() {
	auto p = std::chrono::steady_clock::now();

	if (p >= _nextShoot) {
		_nextShoot += _interval;
		_handler(reinterpret_cast<id_t>(this));
		return true;
	}
	return false;
}

}
