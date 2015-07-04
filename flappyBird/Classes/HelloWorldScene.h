#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "B2Sprite.h"

#define RATIO 48.0f

class HelloWorld : public cocos2d::CCLayer,public b2ContactListener
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    virtual void update(float dt);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void BeginContact(b2Contact* contact);
private:
    cocos2d::CCSize visibleSize;
    b2World* world;     //物理世界
    B2Sprite* bird;
    CCSprite* barContainer;
    void initWorld();
    void addBird();
    void addGround();
    void addBar();
    void addBarContainer();
};

#endif // __HELLOWORLD_SCENE_H__
