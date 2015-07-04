#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    initWorld();
    addBird();
    addBarContainer();
    addGround();
    scheduleUpdate();
    schedule(schedule_selector(HelloWorld::addBar), 1);
    setTouchEnabled(true);
    
    return true;
}

void HelloWorld::addBarContainer()
{
    barContainer = CCSprite::create();
    addChild(barContainer);
}

void HelloWorld::addBar()
{
    float offset = -rand()%5;
    //down bar
    B2Sprite *down_bar = B2Sprite::create("down_bar.png");
    CCSize down_bar_size = down_bar->getContentSize();
    b2BodyDef down_bar_body_def;
    down_bar_body_def.type = b2_kinematicBody;
    down_bar_body_def.position = b2Vec2(visibleSize.width/RATIO,down_bar_size.height/2/RATIO+offset);
    down_bar_body_def.linearVelocity = b2Vec2(-5, 0);
    //添加到body
    b2Body* down_bar_body = world->CreateBody(&down_bar_body_def);
    
    //创建图形 用于碰撞检测
    b2PolygonShape down_bar_shape;
    down_bar_shape.SetAsBox(down_bar_size.width/2/RATIO, down_bar_size.height/2/RATIO);
    b2FixtureDef down_bar_fixture_def;
    down_bar_fixture_def.shape = &down_bar_shape;
    down_bar_body->CreateFixture(&down_bar_fixture_def);
    
    down_bar->setB2Body(down_bar_body);
    down_bar->setPTMRatio(RATIO);
    barContainer->addChild(down_bar);
    
    //up bar
    B2Sprite *up_bar = B2Sprite::create("up_bar.png");
    CCSize up_bar_size = up_bar->getContentSize();
    b2BodyDef up_bar_body_def;
    up_bar_body_def.type = b2_kinematicBody;
    up_bar_body_def.position = b2Vec2(visibleSize.width/RATIO,up_bar_size.height/RATIO+offset+2+up_bar_size.height/2/RATIO);
    up_bar_body_def.linearVelocity = b2Vec2(-5, 0);
    //添加到body
    b2Body* up_bar_body = world->CreateBody(&up_bar_body_def);
    
    //创建图形 用于碰撞检测
    b2PolygonShape up_bar_shape;
    up_bar_shape.SetAsBox(up_bar_size.width/2/RATIO, up_bar_size.height/2/RATIO);
    b2FixtureDef up_bar_fixture_def;
    up_bar_fixture_def.shape = &up_bar_shape;
    up_bar_body->CreateFixture(&up_bar_fixture_def);
    
    up_bar->setB2Body(up_bar_body);
    up_bar->setPTMRatio(RATIO);
    barContainer->addChild(up_bar);

}


void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    bird->getB2Body()->SetLinearVelocity(b2Vec2(0, 5));
}

void HelloWorld::update(float dt)
{
    world->Step(dt, 8, 3);
    
    CCSprite* s;
    for(b2Body* b= world->GetBodyList();b != NULL;b = b->GetNext())
    {
        if(b->GetPosition().x < -3)
        {
            s = (CCSprite*)b->GetUserData();  //移出图片
            if(s != NULL)
            {
                s->removeFromParent();
                CCLog("remove");
            }
            world->DestroyBody(b); //移出body
        }
    }
}

void HelloWorld::initWorld()
{
    world = new b2World(b2Vec2(0,-10));  //向下落 10重力系数
    world->SetContactListener(this);
}

void HelloWorld::BeginContact(b2Contact* contact)
{
    if (contact->GetFixtureA()->GetBody()->GetUserData() == bird
        || contact->GetFixtureB()->GetBody()->GetUserData() == bird)
    {
        
        unscheduleUpdate();
        unschedule(schedule_selector(HelloWorld::addBar));
        CCMessageBox("游戏结速","游戏结束");
        
   
    }
}


void HelloWorld::addGround()
{
    B2Sprite* ground = B2Sprite::create("ground.png");
    CCSize size = ground->getContentSize();
    
    b2BodyDef bDef;
    bDef.type = b2_staticBody;
    bDef.position = b2Vec2(size.width/2/RATIO, size.height/2/RATIO);
    
    b2Body* groundBody =  world->CreateBody(&bDef);
    
    b2PolygonShape groundShape;
    groundShape.SetAsBox(size.width/2/RATIO, size.height/2/RATIO);
    b2FixtureDef def;
    def.shape = &groundShape;
    
    groundBody->CreateFixture(&def);
    
    ground->setB2Body(groundBody);
    ground->setPTMRatio(RATIO);
    addChild(ground);
}

void HelloWorld::addBird()
{
    bird = B2Sprite::create("bird.png");
    
    CCSize size = bird->getContentSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(visibleSize.width/2/RATIO, 9);
    b2Body* birdBody = world->CreateBody(&bodyDef);
    
    //添加一个图形 可用于与其它进行碰撞检测
    b2PolygonShape birdShape;
    birdShape.SetAsBox(size.width/2/RATIO, size.height/2/RATIO);
    
    b2FixtureDef birdFixtureDef;
    birdFixtureDef.shape = &birdShape;
    
    birdBody->CreateFixture(&birdFixtureDef);
    
    bird->setPTMRatio(RATIO);
    bird->setB2Body(birdBody);
    
    addChild(bird);
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
