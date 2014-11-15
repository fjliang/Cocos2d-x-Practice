#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
USING_NS_CC;
class Box2d1 :public Layer 
{
public:
	Box2d1();
	~Box2d1();
	CREATE_FUNC(Box2d1);
	virtual bool init();
	void update(float dt);
	void addWall(float w, float h, float px, float py);
	b2World *world;
};