/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNIT_H
#define UNIT_H

#include <map>
#include <vector>

#include "WorldObject.h"
#include "StateMachine.h"
#include "AnimationTypes.h"
#include "IAnimation.h"

class IAnimation;
class Command;

/**
 * @brief Умный указатель на объект анимации
 */
typedef std::shared_ptr<IAnimation> AnimationPointer;

typedef std::vector<AnimationPointer> AnimationArray;

namespace engine {
    class WorldBuilder;
}

/**
 * @brief Класс юнита
 */
class Unit : public WorldObject {
public:
    friend engine::WorldBuilder;

    Unit();

    virtual ~Unit();

    virtual void doLogic() override;

    virtual void draw(Renderer* renderer) override;

    void setSpeed(double speed);

    double getSpeed() const;

    // временно, пока не реализован нормальный конструктор или фабрика
    //void setAnimation(AnimationType type, const AnimationPointer& animation);
    // временно,
    void setDirection(double direction);

    void setScale(double scale);

    virtual void moveTo(int x, int y);

    // добавить параметр weapon
    virtual void attack(WorldObject& object);

    void changeState(State<Unit>* state);

    void backToPreviousState();

    void changeAnimation(AnimationType type);

private:
    /**
     * @brief Машина состояний
     */
    StateMachine<Unit>* m_stateMachine;

    /**
     * @brief Текущая анимация
     */
    AnimationArray m_currentAnimation;

    /**
     * @brief Мэп анимаций
     */
    std::map<AnimationType, AnimationArray> m_animations;

    /**
     * @brief Направление
     */
    double m_direction;

    double m_speed;

    double m_scale;

    // weapon/item с приоритетом отрисовки в зависимости от направления
    // инвентарь
    // контроллер для управления персонажем
};

#endif // UNIT_H
