#pragma once
#include"cocos2d.h"
USING_NS_CC;

class GameLayer :public cocos2d::Layer
{
public:
	GameLayer();
	~GameLayer();
	CREATE_FUNC(GameLayer);
	bool init();
	void addSprite1(); 
	void addSprite2();
	void addSprite3();
	void addSprite4();
	void addSprite5();

	void update(float dt);
	void addLayer();
	Sequence* action();
	Animate* animate();
};

