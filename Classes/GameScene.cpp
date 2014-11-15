#include "GameScene.h"
#include "Box2dPratice.h"
#include "Box2d1.h"

GameScene::GameScene()
{
	_gameLayer = NULL;
}

GameScene::~GameScene()
{
}

bool GameScene::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Scene::init());

		//_gameLayer = GameLayer::create();
		//CC_BREAK_IF(!_gameLayer);

		//auto layer = Box2dPratice::create();

		auto layer = Box2d1::create();

		this->addChild(layer);
		bRet = true;
	} while (0);
	return bRet;
}
