#include "Box2d1.h"

const float SCALE_RATIO = 32.0f;  //SCALE_RATIOָ���˽���λ������ת���ɵ�λ���׵�ֵ����ΪBOX2Dʹ�õļ�����λ����

Box2d1::Box2d1()
{ 
}
Box2d1::~Box2d1()
{}

bool Box2d1::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());

		Size visibleSize=Director::getInstance()->getVisibleSize();
		Sprite *ball = Sprite::create("ball.png");
		ball->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		this->addChild(ball);

		world = new b2World(b2Vec2(1.0f,-10.0f));

		b2BodyDef bodyDef;
		bodyDef.position.Set(ball->getPosition().x / SCALE_RATIO, ball->getPosition().y / SCALE_RATIO);//����Ҫ������
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData = ball;

		b2CircleShape ballShape;
		ballShape.m_radius = 2;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &ballShape;
		fixtureDef.density = 10.0f;
		fixtureDef.friction = 0.5f;
		fixtureDef.restitution = 0.6f;

		b2Body *body= world->CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);
		body->SetGravityScale(10.0f);

		scheduleUpdate();

		//���һ�����Ϊ1�ĵذ�
		addWall(visibleSize.width, 1, visibleSize.width / 2, 0);

		bRet = true;

	} while (0);
	return bRet;
}

void Box2d1::update(float dt){
	int positionIterations = 10;
	int velocityIterations = 10;
 
	world->Step(dt, velocityIterations, positionIterations);

	for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())
	if (body->GetUserData())
	{
		Sprite *sprite = (Sprite *)body->GetUserData();
		sprite->setPosition(ccp(body->GetPosition().x * SCALE_RATIO, body->GetPosition().y * SCALE_RATIO));
		sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));

	}
	world->ClearForces();
	world->DrawDebugData();
}

void Box2d1::addWall(float w, float h, float px, float py){
	b2PolygonShape floorShape;//�ذ�
	floorShape.SetAsBox(w/SCALE_RATIO,h/SCALE_RATIO);

	b2FixtureDef floorFixtureDef;
	floorFixtureDef.density = 0;
	floorFixtureDef.friction = 10;
	floorFixtureDef.restitution = 0.6f;
	floorFixtureDef.shape = &floorShape;

	b2BodyDef floorBodyDef;
	floorBodyDef.position.Set(px / SCALE_RATIO, py / SCALE_RATIO);//��/2   ��/2

	b2Body *floorBody = world->CreateBody(&floorBodyDef);
	floorBody->CreateFixture(&floorFixtureDef);

}