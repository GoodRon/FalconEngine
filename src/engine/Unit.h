/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNIT_H
#define UNIT_H

#include <map>

#include "WorldObject.h"
#include "StateMachine.h"
//#include "AnimationTypes.h"
#include "Animation.h"

//class IAnimation;
//class Command;

/**
 * @brief Умный указатель на объект анимации
 */
//typedef std::shared_ptr<IAnimation> AnimationPointer;

//typedef std::vector<AnimationPointer> AnimationArray;

/*
namespace engine {
    class WorldBuilder;
}
*/

/**
 * @brief Класс юнита
 */
class Unit : public WorldObject {
public:
//    friend engine::WorldBuilder;

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

private:
    /**
     * @brief Машина состояний
     */
    StateMachine<Unit>* _stateMachine;

    /**
     * @brief Текущая анимация
     */
    //AnimationArray _currentAnimation;

    /**
     * @brief Мэп анимаций
     */
    //std::map<AnimationType, AnimationArray> m_animations;
    std::map<int, Animation> _animations;

    /**
     * @brief Направление
     */
    double _direction;

    double _speed;

    double _scale;

    // weapon/item с приоритетом отрисовки в зависимости от направления
    // инвентарь
    // контроллер для управления персонажем
};

#endif // UNIT_H
