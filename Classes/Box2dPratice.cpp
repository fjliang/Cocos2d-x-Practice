#include "Box2dPratice.h"

const float SCALE_RATIO = 32.0f;  //SCALE_RATIO指出了将单位：像素转换成单位：米的值，因为BOX2D使用的计量单位是米

Box2dPratice::Box2dPratice()
{
	//b2Vec2 gravity;
	//gravity.Set(0.0f, -10.0f);//物理世界的重力（垂直向下）
	//b2World	*world = new b2World(gravity); //创建世界对象

	//b2PolygonShape worldShape;
	//worldShape.SetAsBox(100.0f, 100.0f);

	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;//静止的
	//bodyDef.position.Set(50.0f, 50.0f);

	//world->CreateBody(&bodyDef);

 
}

  bool Box2dPratice::init(){
	bool bRet = false;

	do{
		CC_BREAK_IF(!Layer::init());
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(Box2dPratice::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(Box2dPratice::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(Box2dPratice::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		dragOffsetStartX = 0;
		dragOffsetEndX = 0; 
		dragOffsetStartY = 0;
		dragOffsetEndY = 0;
		existBall = false;
		ballX = 300.0f;
		ballY = 300.0f;
		powerMultiplier = 10;
		ball = Sprite::create("ball.png");
		ball->setPosition(Point(ballX, ballY));
		this->addChild(ball);

		world = new b2World(b2Vec2(0.0f,-10.0f)); //Y轴重力加速度10
		//defineBall();
		scheduleUpdate();

		Size visibleSize = Director::getInstance()->getVisibleSize();

		addWall(visibleSize.width, 10, (visibleSize.width / 2), 0); //CEIL
		addWall(10, visibleSize.height, 0, (visibleSize.height / 2)); //LEFT
		addWall(10, visibleSize.height, visibleSize.width, (visibleSize.height / 2)); //RIGHT

		for (int i = 1; i <= 31; i++){
			points[i] = CCSprite::create("dot.png");
			this->addChild(points[i]);
		}


		bRet = true;
	} while (0);
	return bRet;
}

bool Box2dPratice::onTouchBegan(Touch* touch, Event* event){
	dragOffsetStartX = touch->getLocation().x;
	dragOffsetStartY = touch->getLocation().y;

	CCPoint touchLocation = touch->getLocation();

	ballX = touchLocation.x;
	ballY = touchLocation.y;

	if (existBall){
		world->DestroyBody(ballBody);
	}

	ball->setPosition(ccp(ballX, ballY));
	return true;

}
void Box2dPratice::onTouchMoved(Touch* touch, Event* event){
	Point touchLocation = touch->getLocation();

	dragOffsetEndX = touchLocation.x;
	dragOffsetEndY = touchLocation.y;

	float dragDistanceX = dragOffsetStartX - dragOffsetEndX;
	float dragDistanceY = dragOffsetStartY - dragOffsetEndY;

	//Box2dPratice::simulateTrajectory(b2Vec2((dragDistanceX) / SCALE_RATIO, (dragDistanceY) / SCALE_RATIO));
	Box2dPratice::simulateTrajectory(b2Vec2((dragDistanceX * powerMultiplier) / SCALE_RATIO, (dragDistanceY * powerMultiplier) / SCALE_RATIO));
}
void Box2dPratice::onTouchEnded(Touch* touch, Event* event){
	existBall = true;

	Box2dPratice::defineBall();

	Point touchLocation = touch->getLocation();

	dragOffsetEndX = touchLocation.x;
	dragOffsetEndY = touchLocation.y;

	float dragDistanceX = dragOffsetStartX - dragOffsetEndX;
	float dragDistanceY = dragOffsetStartY - dragOffsetEndY;

	//ballBody->SetLinearVelocity(b2Vec2((dragDistanceX) / SCALE_RATIO, (dragDistanceY) / SCALE_RATIO));
	ballBody->SetLinearVelocity(b2Vec2((dragDistanceX * powerMultiplier) / SCALE_RATIO, (dragDistanceY * powerMultiplier) / SCALE_RATIO));
}

void Box2dPratice::defineBall(){
	ballShape.m_radius = 45 / SCALE_RATIO;
	b2FixtureDef ballFixture;
	ballFixture.density = 10;
	ballFixture.friction = 0.8;
	ballFixture.restitution = 0.6;
	ballFixture.shape = &ballShape;

	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.userData = ball;

	ballBodyDef.position.Set(ball->getPosition().x / SCALE_RATIO, ball->getPosition().y / SCALE_RATIO);

	ballBody = world->CreateBody(&ballBodyDef);
	ballBody->CreateFixture(&ballFixture);
	ballBody->SetGravityScale(10);

}

void Box2dPratice::update(float dt){
	int positionIterations = 10;
	int velocityIterations = 10;

	deltaTime = dt;
	world->Step(dt, velocityIterations, positionIterations);

	for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())
	if (body->GetUserData())
	{
		CCSprite *sprite = (CCSprite *)body->GetUserData();
		sprite->setPosition(ccp(body->GetPosition().x * SCALE_RATIO, body->GetPosition().y * SCALE_RATIO));
		sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));



	}
	world->ClearForces();
	world->DrawDebugData();
}

void Box2dPratice::addWall(float w, float h, float px, float py) {

	b2PolygonShape floorShape;

	floorShape.SetAsBox(w / SCALE_RATIO, h / SCALE_RATIO);
	b2FixtureDef floorFixture;
	floorFixture.density = 0;
	floorFixture.friction = 10;
	floorFixture.restitution = 0.5;
	floorFixture.shape = &floorShape;
	b2BodyDef floorBodyDef;

	floorBodyDef.position.Set(px / SCALE_RATIO, py / SCALE_RATIO);
	b2Body *floorBody = world->CreateBody(&floorBodyDef);

	floorBody->CreateFixture(&floorFixture);

}


void Box2dPratice::simulateTrajectory(b2Vec2 coord)
{
	Box2dPratice::defineBall();

	ballBody->SetLinearVelocity(b2Vec2(coord.x, coord.y));
	for (int i = 1; i <= 31; i++){
		world->Step(deltaTime, 10, 10);
		points[i]->setPosition(CCPoint(ballBody->GetPosition().x*SCALE_RATIO, ballBody->GetPosition().y*SCALE_RATIO));
		world->ClearForces();

	}

	world->DestroyBody(ballBody);
}

Box2dPratice::~Box2dPratice()
{
}
