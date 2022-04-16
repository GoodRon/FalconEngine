/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_IENTITY_H
#define FALCON_IENTITY_H

namespace falcon {

using EntityID = int;

class IEntity {
public:
	IEntity();
	virtual ~IEntity() = 0;

	EntityID getId() const;

private:
	EntityID _id;
};

}

#endif // FALCON_IENTITY_H
