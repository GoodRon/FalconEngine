/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>
#include <SDL2/SDL.h>

#include "Engine.h"
#include "EngineException.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimerPool.h"
#include "Tile.h"
#include "Field.h"
#include "ObjectManager.h"

#include <vector>
#include <memory>

int main() {
    try {
        Engine engine(1280, 768);
    
        // Конструируем поле (пока руками)
        std::shared_ptr<Tile> grassTile(new Tile(engine.getResourceManager()->loadTexture("grass.png")));
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
        for (int i = 0; i < 3; ++i) {
            std::vector<std::shared_ptr<Tile>> row;
            tiles.push_back(row);
            for (int j = 0; j < 5; ++j) {
                tiles[i].push_back(grassTile);
            }
        }
        
        std::shared_ptr<Field> grassField(new Field(tiles));
        grassField->setPosition(40, 40);
        engine.getObjectManager()->pushObject(
            std::dynamic_pointer_cast<WorldObject>(grassField));
        
        engine.getTimersPool()->addTimer(33, [&engine](TimerPool::id_t) {
            engine.getObjectManager()->drawAllObjects();
        });
        
        return engine.execute();
    } catch (EngineException& exception) {
        std::cout << "Exception caught: " << exception.what() << std::endl;
    }
    return -1;
}
