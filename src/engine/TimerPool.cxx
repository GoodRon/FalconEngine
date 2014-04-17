/*
 *  Copyright (c) 2013, Troshin V.S., Incom inc Tomsk Russia
 *  All rights reserved.
 */

#include <algorithm>

#include "TimerPool.h"

using namespace std;
using namespace std::chrono;

TimerPool::id_t TimerPool::addTimer ( uint32_t milliseconds, TimerHandler handler, bool oneshoot ) {
	Timer *timer = new Timer( milliseconds, handler, oneshoot );
	timers.emplace_front( timer );
	return reinterpret_cast<id_t>(timer);
}


void TimerPool::check() {
	timers.remove_if([](TimerPointer &x) {
		if( x->m_flags.deleted ) {
			return true;
		}

		if( x->check() ) {
			// не в одном предикате из-за порядка вычисления ( oneshoot_ может быть
			// изменен внутри check!
			return x->m_flags.oneshoot;
		}
		return false;
	});
}


bool TimerPool::getNextShootTimeInterval ( struct timeval &tv ) {
	if( timers.empty() ) {
		return false;
	}

	auto it = min_element(timers.begin(), timers.end(), [](const TimerPointer& lhs, const TimerPointer& rhs) {
		return *lhs < *rhs;
	});
	microseconds delta = duration_cast<std::chrono::microseconds>((*it)->m_next_shoot - steady_clock::now());

	if( delta.count() <= 0 ) {
		tv.tv_sec = 0;
		tv.tv_usec = 0;
	} else {
		tv.tv_sec = delta.count()/1000000;
		tv.tv_usec = delta.count()%1000000;
	}
	return true;
}


void TimerPool::deleteTimer ( id_t id ) {
	for( auto &x: timers ) {
		if( reinterpret_cast<id_t>(x.get()) == id ) {
			x->m_flags.deleted = true;
		}
	}
}


TimerPool::Timer::Timer( uint32_t millisec, TimerPool::TimerHandler handler, bool oneshoot )
	:
	m_interval(millisec),
	m_handler(handler),
	m_next_shoot(steady_clock::now() + m_interval),
	m_flags({oneshoot, false}) {
}


bool TimerPool::Timer::check() {
	steady_clock::time_point p = steady_clock::now();

	if( p >= m_next_shoot ) {
		m_next_shoot += m_interval;
		m_handler(reinterpret_cast<id_t>(this));
		return true;
	}
	return false;
}
