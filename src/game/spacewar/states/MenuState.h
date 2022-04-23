/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MENU_STATE_H
#define SW_MENU_STATE_H

#include <forward_list>
#include <string>

#include <firefly/IGameState.h>
#include <firefly/Types.h>

namespace firefly {
	class IEvent;
	class Engine;
}

namespace spacewar {

class MenuState final: public firefly::IGameState {
public:
	MenuState(firefly::Engine* engine);
	~MenuState() override;

	MenuState(const MenuState&) = delete;
	MenuState& operator=(MenuState&) = delete;

	void onEnter() override;
	void onExit() override;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	void buildObjects();
	void destroyObjects();
	void setObjectsActive(bool isActive);

	void buildSystems();
	void destroySystems();
	void setSystemsActive(bool isActive);

private:
	std::forward_list<firefly::EntityID> _objectIds; 
	std::forward_list<std::string> _systemNames;
};


#endif // SW_MENU_STATE_H
