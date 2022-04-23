/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_GAME_STATE_H
#define SW_SYSTEMS_GAME_STATE_H

#include <memory>
#include <unordered_map>

namespace spacewar {

class IGameState;

class GameStates final: public firefly::ISystem {
public:
	GameSystem(firefly::Engine* engine);
	~GameSystem() override;

	GameSystem(const GameSystem&) = delete;
	GameSystem& operator=(const GameSystem&) = delete;

	bool registerState(
		int stateId, const std::unique_ptr<IGameState>& state);

	bool switchState(int stateId);

	void clearStates();

private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;
	void onUpdate() override;

private:
	int _currentStateId;
	std::unordered_map<int, std::unique_ptr<IGameState>> _states;
};

}

#endif // SW_SYSTEMS_GAME_STATE_H
