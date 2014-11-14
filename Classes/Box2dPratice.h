#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
USING_NS_CC;
class Box2dPratice :public Layer ,public b2ContactListener
{
public:
	Box2dPratice();
	~Box2dPratice();
	CREATE_FUNC(Box2dPratice);
	virtual bool init();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	int dragOffsetStartX;
	int dragOffsetEndX;
	int dragOffsetStartY;
	int dragOffsetEndY;
	bool existBall;
	float ballX;
	float ballY;
	Sprite *ball;
	b2Body *ballBody;
	b2CircleShape ballShape;
	b2BodyDef ballBodyDef;
	b2World *world;
	float deltaTime;
	float powerMultiplier;
	Sprite *points[32];
	void defineBall();
	void update(float dt);
	void addWall(float w, float h, float px, float py);
	void simulateTrajectory(b2Vec2 coord);
};

