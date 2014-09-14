/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <map>
#include <functional>
#include <chrono>
#include <memory>

#include "WorldObject.h"
#include "DirectedAnimation.h"

struct SDL_Rect;
class Target;

struct UnitState {
	std::string animation;
	std::function<void()> logic;
};

class Unit: public WorldObject {
public:
	Unit(const std::string& name);
	
	virtual ~Unit();

	void setAnimations(const map<std::string, DirectedAnimation>& animations);
	
	virtual void draw(Renderer* renderer);

	virtual void doLogic(const std::chrono::milliseconds& timeDelta);

	void setSpeed(double speed);

	void moveTo(int x, int y);

	void stop();

	// void attack(const std::shared_ptr<Target>& target);

	// SDL_Rect getCollisionBounds() const;

private:
	std::string m_name;
	std::shared_ptr<Target> m_target;
	double m_speed;
	// Inventory m_inventory;
	// Skills m_states;
	map<std::string, DirectedAnimation> m_animations;
};

#endif // UNIT_H
