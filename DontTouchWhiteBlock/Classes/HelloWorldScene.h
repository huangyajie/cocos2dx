#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

class HelloWorld : public cocos2d::CCLayer
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
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void update(float dt);
private:
    cocos2d::CCSize visibleSize ;
    int linesCount;
    bool isShowEndLine;
    long initTime;
    cocos2d::CCLabelTTF* scoreLabel;
    cocos2d::CCLayer* gameLayer;
    
    void addStartLine();
    void addEndLine();
    
    void addNormalLine(int row);
    void startGame();
    void moveDown();
    
    void startTimer();
    void stopTimer();
    bool isTimerRunnig;
};

#endif // __HELLOWORLD_SCENE_H__
