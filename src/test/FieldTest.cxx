/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <vector>
#include <memory>
#include <iostream>

#include <SDL2/SDL.h>

#include "Engine.h"
#include "EngineException.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimerPool.h"
#include "Tile.h"
#include "IsometricField.h"
#include "ObjectManager.h"

int main() {
    try {
        Engine engine(1280, 768);
    
        // Конструируем поле (пока руками)
        SDL_Rect tileSize = {0, 0, 128, 64};
        std::shared_ptr<Tile> grassTile(new Tile(engine.getResourceManager()->
        								loadTexture("resources/grass3.png")));
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
        for (int i = 0; i < 9; ++i) {
            std::vector<std::shared_ptr<Tile>> row;
            tiles.push_back(row);
            for (int j = 0; j < 5; ++j) {
                tiles[i].push_back(grassTile);
            }
        }
        
        std::shared_ptr<IsometricField> grassField(new IsometricField(tiles, tileSize));
        engine.getObjectManager()->pushObject(
            std::dynamic_pointer_cast<WorldObject>(grassField));
        
        engine.getTimersPool()->addTimer(33, [&engine, grassField](TimerPool::id_t) {
            engine.getRenderer()->clear();
            engine.getObjectManager()->drawAllObjects();
            //SDL_Rect fieldPosition = grassField->getPosition();
            //fieldPosition.x += 1;
            //grassField->setPosition(fieldPosition.x, fieldPosition.y);
        });
        
        return engine.execute();
    } catch (EngineException& exception) {
        std::cout << "Exception caught: " << exception.what() << std::endl;
    }
    return -1;
}
