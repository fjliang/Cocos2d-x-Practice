#include "GameLayer.h"

Size winSize;
Vector<Sprite*> vec;
Vector<String*> str;
Array* arr;
 
GameLayer::GameLayer()
{
	winSize = Director::getInstance()->getWinSize();
	arr = Array::create();
	arr->retain();
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
		//schedule(schedule_selector(GameLayer::update), 2.0f, kRepeatForever, 0);
		//addSprite1();
		//addLayer();
		//particle();
		test();
	 
	} while (0);
	return bRet;
}
void GameLayer::test(){
	Sprite* sp = Sprite::create("angry_birds_01.png");
	vec.pushBack(sp);
	vec.pushBack(sp);
	vec.pushBack(sp);
	vec.pushBack(sp);
	vec.pushBack(sp);
	vec.pushBack(sp);
	vec.pushBack(sp);
	for (Sprite* s : vec)
	{
		log("arrayCount----------->" + vec.size());
	}
	String* x = String::create("x");
	 
	str.pushBack(&String("cc"));
	 
 
	for (String*  ss : str)
	{
		log("str----------->" + str.size());
	}

	arr->addObject(sp);
	arr->addObject(sp);
	arr->addObject(sp);
	arr->addObject(sp);
	arr->addObject(sp);

	Object* obj;
	CCARRAY_FOREACH(arr,obj){
		log("CCARRAY_FOREACH----------->" + arr->count());
	}
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
	auto hide= Hide::create();
	MoveTo* moveTo1 = MoveTo::create(2, ccp(50, 50));
	MoveTo* moveTo2 = MoveTo::create(2, ccp(300, 300));
	auto moveBy= MoveBy::create(2,ccp(80,50));

	auto jumpTo=JumpTo::create(2,ccp(250,250),10,5);
	auto jumpBy=JumpBy::create(2,ccp(100,100),10,5);
	auto blink=Blink::create(2,4);
	 
	auto xx = CallFunc::create(this, callfunc_selector(GameLayer::addSprite1));

	return Sequence::create(fx, moveTo1, moveTo2, moveBy, jumpTo, jumpBy, blink, hide, xx, NULL);
}

Animate* GameLayer::animate(){
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plist/birds.plist");
	 
	Animation* animation=Animation::create();
	animation->setDelayPerUnit(0.2f);
	 
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("angry_birds_01.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("angry_birds_02.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("angry_birds_03.png"));
	 
	return Animate::create(animation);
}
BezierTo* GameLayer::bezierAction(){
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(winSize.width / 2, winSize.height / 2);
	bezier.controlPoint_2 = Point(200, 200);
	bezier.endPosition = Point(50,100);
	return BezierTo::create(3.0f, bezier);
}

Spawn*  GameLayer::spawn(){
	FadeIn* fadeIn= FadeIn::create(5.0f);
	ScaleTo* scaleTo= ScaleTo::create(2.0f,0.5f);
	RotateBy* rotateBy= RotateBy::create(2.0f,90,180);
	SkewTo* skewTo= SkewTo::create(2.0,60,60);
	EaseCircleActionIn* easeCircleActionIn= EaseCircleActionIn::create(rotateBy);
	
	return Spawn::create(fadeIn, scaleTo, easeCircleActionIn, skewTo, NULL);

}

ParticleSystemQuad* GameLayer::particle(){
	ParticleSystemQuad* emitter = ParticleSystemQuad::createWithTotalParticles(100);

	emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("CloseNormal.png"));
	emitter->setDuration(ParticleSpiral::DURATION_INFINITY);
	emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);
	emitter->setStartRadius(4);
	emitter->setStartRadiusVar(1);
	emitter->setEndRadius(ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS);
	emitter->setEndRadiusVar(0);

	// radius mode: degrees per second
	emitter->setRotatePerSecond(100);
	emitter->setRotatePerSecondVar(0);

	// angle
	emitter->setAngle(90);
	emitter->setAngleVar(0);

	// emitter position
	auto size = Director::getInstance()->getWinSize();
	emitter->setPosVar(Point::ZERO);

	// life of particles
	emitter->setLife(0.5);
	emitter->setLifeVar(0);

	// spin of particles
	emitter->setStartSpin(0);
	emitter->setStartSpinVar(0);
	emitter->setEndSpin(0);
	emitter->setEndSpinVar(0);

	// color of particles
	Color4F startColor(0.0f, 0.8f, 0.9f, 1.0f);
	emitter->setStartColor(startColor);

	Color4F startColorVar(0, 0, 0, 1.0f);
	emitter->setStartColorVar(startColorVar);

	Color4F endColor(1.0f, 1.0f, 1.0f, 0.1f);
	emitter->setEndColor(endColor);

	Color4F endColorVar(0, 0, 0, 0.1f);
	emitter->setEndColorVar(endColorVar);

	// size, in pixels
	emitter->setStartSize(20);
	emitter->setStartSizeVar(1);
	emitter->setEndSize(0);

	emitter->setPosition(200,200);

	// emits per second
	emitter->setEmissionRate(emitter->getTotalParticles() / emitter->getLife());

	// additive
	emitter->setBlendAdditive(false);

	addChild(emitter, 5);

	return emitter;

}

void GameLayer::addSprite1(){
	//直接添加
	Sprite* sprite = Sprite::create("angry_birds_01.png");
	sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	//设置锚点，默认图片中心
	//sp->setAnchorPoint(ccp(0, 0));
	this->addChild(sprite);
	//sprite->runAction(action());
	sprite->runAction(RepeatForever::create( animate()));
	//sprite->runAction(RepeatForever::create(bezierAction()));
	//sprite->runAction(RepeatForever::create(spawn()));

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