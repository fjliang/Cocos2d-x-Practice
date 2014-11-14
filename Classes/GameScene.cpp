#include "GameScene.h"
#include "Box2dPratice.h"

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

		auto layer = Box2dPratice::create();

		this->addChild(layer);
		bRet = true;
	} while (0);
	return bRet;
}
