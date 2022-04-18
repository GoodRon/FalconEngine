#ifndef FIREFLY_TIMER_POLL_H
#define FIREFLY_TIMER_POLL_H

#include <memory>
#include <functional>
#include <forward_list>
#include <chrono>
#include <winsock.h>

namespace firefly {

class TimerPool {
public:

#ifdef __x86_64__
	using id_t = uint64_t;
#else
	using id_t = uint32_t;
#endif

	TimerPool();

	~TimerPool();

	TimerPool(const TimerPool&) = delete;
	TimerPool& operator=(const TimerPool&) = delete;

	using TimerHandler = std::function<void (id_t)>;

	id_t addTimer(uint32_t milliseconds, 
		TimerHandler handler, bool oneshoot = false);

	void deleteTimer(id_t id);

	void check();

	bool getNextShootTimeInterval(struct timeval& tv);

private:
	struct Timer {
		Timer(uint32_t milliseconds, TimerHandler handler, bool oneshoot);

		struct Flags {
			bool oneshoot:1;
			bool deleted:1;
		};
		
		bool check();

		bool operator<(const Timer& b) {
			return this->_nextShoot < b._nextShoot;
		}

		std::chrono::milliseconds _interval;
		TimerHandler _handler;
		std::chrono::steady_clock::time_point _nextShoot;
		Flags _flags;
	};

	using TimerPointer = std::unique_ptr<Timer>;

	std::forward_list<TimerPointer> _timers;
};

}

#endif // FIREFLY_TIMER_POLL_H
