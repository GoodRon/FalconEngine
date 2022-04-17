/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_WORLD_OBJECT_H
#define FALCON_WORLD_OBJECT_H

struct SDL_Rect;

namespace falcon {

class Renderer;
class Command;

class WorldObject {
public:
	WorldObject(int x, int y);

	WorldObject();

	virtual ~WorldObject() = 0;

	int getId() const;

	virtual void setPosition(int x, int y);
	virtual SDL_Rect getPositionAndProfile() const;

	virtual SDL_Rect getProfile() const;
	virtual SDL_Rect getPosition() const;

	virtual void draw(Renderer* renderer) = 0;

	virtual void executeCommand(Command* command);

	virtual void doLogic();

	// cacheFullState();

	// isCollide();

	virtual int getDrawPriority();

	void setVisibility(bool isVisible);

	bool getVisibility() const;

protected:
	int _id;
	int _x;
	int _y;
	int _width;
	int _height;
	bool _isVisible;
};

}

#endif // FALCON_WORLD_OBJECT_H
