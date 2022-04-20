/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_GRAVITATION_H
#define SW_SYSTEMS_GRAVITATION_H

#include <unordered_map>

#include <firefly/systems/ISystem.h>
#include <firefly/Types.h>

namespace firefly {
	class Entity;
}

namespace spacewar {

class GravitationalSystem final: public firefly::ISystem {
public:
	GravitationalSystem(firefly::Engine* engine);
	~GravitationalSystem() override;

	GravitationalSystem(const GravitationalSystem&) = delete;
	GravitationalSystem& operator=(const GravitationalSystem&) = delete;

	void update() override;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	void onRegisterEntity(firefly::Entity* entity) override;
	void onUnregisterEntity(firefly::Entity* entity) override;

	void processGravity(
		firefly::Entity* gravityEmitter,
		uint64_t elapsedMs) const;

private:
	std::unordered_map<firefly::EntityID, firefly::Entity*> _gravityEmitters;
};

}

#endif // SW_SYSTEMS_GRAVITATION_H
