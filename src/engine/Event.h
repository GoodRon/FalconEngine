/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef EVENT_H
#define EVENT_H

/**
 * @brief Перечисление типов событий
 **/
enum EventType {

	etDummy = 0,

	etSdlEvent = 1
};

/**
 * @brief Абстрактный класс события
 **/
class Event {
public:
	/**
	 * @brief Конструктор
	 *
	 * @param type тип события
	 **/
	Event(EventType type);

	/**
	 * @brief Деструктор
	 **/
	virtual ~Event() = 0;

	/**
	 * @brief Вернуть тип события
	 *
	 * @return EventType
	 **/
	EventType getType();

private:
	/**
	 * @brief Тип события
	 **/
	EventType m_type;
};

#endif // EVENT_H
