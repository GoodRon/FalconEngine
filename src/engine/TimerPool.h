/*
 *  Copyright (c) 2013, Troshin V.S., Incom inc Tomsk Russia
 *  All rights reserved.
 */

#ifndef TIMERSPOLL_H
#define TIMERSPOLL_H

#include <memory>
#include <functional>
#include <forward_list>
#include <chrono>

/**
 * @brief Пул таймеров
 **/
class TimerPool {
public:
	/**
	* @brief Описатель идентификатора таймера
	**/
#ifdef __x86_64__
	typedef uint64_t id_t;
#else
	typedef uint32_t id_t;
#endif

	static TimerPool& getInstance() {
		static TimerPool manager;
		return manager;
	}

	/**
	 * @brief Описатель обработчика сигнала таймера
	 **/
	typedef std::function<void ( id_t ) > TimerHandler;


	/**
	 * @brief Добавить таймер в пул
	 *
	 * @param milliseconds - количество милисекунд до срабатывания
	 * @param handler - обработчик срабатывания таймера
	 * @param oneshoot - таймер работает один раз и удаляется
	 * @return идентификатор вновь созданного таймера
	 **/
	id_t addTimer ( uint32_t milliseconds, TimerHandler handler, bool oneshoot = false );


	/**
	 * @brief Удалить таймер по его идентификатору
	 *
	 * @param id - идентификатор таймера
	 **/
	void deleteTimer ( id_t id );


	/**
	 * @brief Проверка срабатывания таймеров
	 **/
	void check();


	/**
	 * @brief Получить ближайшее время срабатывания какого-либо таймера
	 *
	 * Если нет таймеров, то tv в неопределенном состоянии
	 * @param tv - структура для заполнения
	 * @return false, если не таймеров
	 **/
	bool getNextShootTimeInterval ( struct timeval &tv );

private:
	TimerPool() : timers() {}
	~TimerPool() {}

	TimerPool(const TimerPool& other) = delete;
	TimerPool& operator=(TimerPool& other) = delete;

	/**
	* @brief Достаточно точный программный таймер
	*
	* Таймер после срабатывания генерирует сигнал signal_Shoot, в котором предает собственный ID.
	* Если в конструкторе был установлен параметр oneshoot, то после первого срабатывания таймер
	* удаляется из пула таймеров.
	**/
	struct Timer {
		/**
		 * @brief Конструктор
		 * @param milliseconds - время отсчета до срабатывания таймера в миллисекундах
		 * @param handler - обработчик срабатывания
		 * @param oneshoot - одноразовый таймер
		 **/
		Timer ( uint32_t milliseconds, TimerHandler handler, bool oneshoot);


		/**
		 * @brief Интервал срабатывания в милисекундах
		 **/
		std::chrono::milliseconds m_interval;


		/**
		 * @brief Сигнал по срабатыванию таймера
		 **/
		TimerHandler m_handler;


		/**
		 * @brief Время последнего срабатывания
		 **/
		std::chrono::steady_clock::time_point m_next_shoot;

		/**
		 * @brief Сборка булевых флагов
		 **/
		typedef struct {
			/**
			* @brief Признак одноразового таймера
			**/
			bool oneshoot:1;

			/**
			 * @brief Признак того, что таймер удален
			 **/
			bool deleted:1;
		} Flags;


		/**
		 * @brief Флаги таймера
		 **/
		Flags m_flags;


		/**
		 * @brief Проверка срабатывания ( выполняет пул )
		 *
		 * В этом методе происходит вызов сигнала и новый взвод таймера
		 * @return bool
		 **/
		bool check();


		/**
		 * @brief Оператор сравнения
		 *
		 * @param b - с чем сравнить
		 * @return bool
		 **/
		bool operator < (const Timer& b) {
			return this->m_next_shoot < b.m_next_shoot;
		}
	};

	/**
	 * @brief Умный указатель на таймер
	 **/
	typedef std::unique_ptr<Timer> TimerPointer;


	/**
	 * @brief Все таймеры пула
	 **/
	std::forward_list<TimerPointer> timers;
};

#endif // TIMERSPOLL_H
