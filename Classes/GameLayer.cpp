#include "GameLayer.h"

Size winSize;
GameLayer::GameLayer()
{
	winSize = Director::getInstance()->getWinSize();
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());
		bRet = true;

		//scheduleUpdate();

		schedule(schedule_selector(GameLayer::update), 2.0f, kRepeatForever, 0);
		addSprite1();
		addLayer();
	} while (0);
	return bRet;
}

void GameLayer::update(float dt){
	log("update");
}

void GameLayer::addLayer(){
	LayerColor* layerColor = LayerColor::create(Color4B(100, 100, 100, 100), winSize.width / 2, winSize.height / 2);
	LayerColor* layerColor2 = LayerColor::create(Color4B(100, 100,200, 200), winSize.width / 4, winSize.height / 4);
	layerColor2->ignoreAnchorPointForPosition(false);
	layerColor2->setAnchorPoint(ccp(0.5,0.5));
	this->addChild(layerColor);
	this->addChild(layerColor2);
}

Sequence*  GameLayer::action(){
	FlipX* fx = FlipX::create(true);
	MoveTo* moveTo= MoveTo::create(2, ccp(0, 0));
	return Sequence::create(moveTo, fx, moveTo->reverse(), NULL);
}

void GameLayer::addSprite1(){
	//直接添加
	Sprite* sprite = Sprite::create("angry_birds_01.png");
	sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	//设置锚点，默认图片中心
	//sp->setAnchorPoint(ccp(0, 0));
	this->addChild(sprite);
	sprite->runAction(action());
}

void GameLayer::addSprite2(){
	//截取图片的矩形区域
	Sprite* sprite = Sprite::create("angry_birds_01.png", Rect(0, 0, 100, 100));
	sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(sprite);
}

void GameLayer::addSprite3(){
	//全局缓存
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plist/birds.plist");
	Sprite* sprite = Sprite::createWithSpriteFrameName("angry_birds_02.png");
	sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(sprite);

}

void GameLayer::addSprite4(){
	SpriteFrame* spriteFrame = SpriteFrame::create("angry_birds_01.png", Rect(0, 0, 100, 100));
	Sprite* sprite = Sprite::createWithSpriteFrame(spriteFrame);
	sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(sprite);

}

void GameLayer::addSprite5(){
	//批处理  适合大量重复的图片（子弹）
	SpriteBatchNode* spriteBatchNode = SpriteBatchNode::create("angry_birds_01.png");
	Sprite* sprite = Sprite::createWithTexture(spriteBatchNode->getTexture());
	sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	spriteBatchNode->addChild(sprite);
	this->addChild(spriteBatchNode);

}