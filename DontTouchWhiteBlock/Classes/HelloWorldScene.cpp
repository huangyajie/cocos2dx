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
    srand(time(NULL));
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    addStartLine();
//    addEndLine();
   
    
    isTimerRunnig = false;
    
    //后面新增加的块 会把时间给覆盖 ，因此要新增加一个层
    gameLayer = CCLayer::create();
    addChild(gameLayer);

    scoreLabel = CCLabelTTF::create();
    scoreLabel->setString("0.000000");
    scoreLabel->setColor(ccc3(0,0,255));
    scoreLabel->setPosition(ccp(visibleSize.width/2,visibleSize.height-70));
    scoreLabel->setFontSize(50);
    addChild(scoreLabel);
    
    startGame();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    
    return true;
}



void HelloWorld::addStartLine()
{
    ccColor3B color;
    color.r = 255;
    color.g = 255;
    color.b = 0;
    auto b = Block::create(color,CCSize(visibleSize.width, visibleSize.height/4), "", 20, color);
    
    gameLayer->addChild(b);
    b->setRow(0);
    
}

void HelloWorld::addEndLine()
{
    ccColor3B color;
    color.r = 0;
    color.g = 255;
    color.b = 0;
    
    ccColor3B color2;
    color2.r = 255;
    color2.g = 0;
    color2.b = 0;
    auto b = Block::create(color,CCSize(visibleSize.width, visibleSize.height), "Game Over", 30, color2);
    
    gameLayer->addChild(b);
    b->setRow(4);

}

void HelloWorld::addNormalLine(int row)
{
    
    int r = rand()%4;
    for (int i = 0 ; i < 4; i++) {
        auto b = Block::create(r == i ? ccc3(0,0,0):ccc3(255,255,255),CCSize(visibleSize.width/4 -1,visibleSize.height/4 -1), "", 10,ccc3(1,1,1));
        gameLayer->addChild(b);
        b->setPosition(ccp(visibleSize.width/4 *i,visibleSize.height/4*row));
        b->setRow(row);
    }
    linesCount ++;
}

void HelloWorld::startGame()
{
    linesCount = 0;
    isShowEndLine = false;
    addStartLine();
    addNormalLine(1);
    addNormalLine(2);
    addNormalLine(3);
}

void HelloWorld::moveDown()
{
    if(linesCount < 20)
    {
        addNormalLine(4);
    }
    else
    {
        if(!isShowEndLine)
        {
            addEndLine();
            isShowEndLine = true;
        }
    }
    
    std::vector<Block*>* bv = Block::getBlocks();
    for (auto it = bv->begin() ; it != bv->end(); it++) {
        (*it)->moveDown();
    }

}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLog("123");
    std::vector<Block*>* bv = Block::getBlocks();
    for (auto it = bv->begin(); it != bv->end(); it++) {
        auto b = *it;
        if (b->getRow() == 1
            && b->boundingBox().containsPoint(pTouch->getLocation())) {
            
            
            if(b->getColor().r == 0
               && b->getColor().g == 0
               && b->getColor().b == 0 )
            {
                moveDown();
                b->setColor(ccc3(96,96,96));
                startTimer();
            }
            
            else if(b->getColor().r == 0
               && b->getColor().g == 255
               && b->getColor().b == 0 )
            {
                moveDown();
                stopTimer();
            }

            else
            {
                CCMessageBox("GameOver", "失败");
            }
            
            break;

        }
    }
    
    return false;
}

void HelloWorld::update(float dt)
{
    long offset = clock() - initTime;  //us
    char buf[32] = {0};
    sprintf(buf, "%g",(double)offset/1000000);
    scoreLabel->setString(buf);
}

void HelloWorld::startTimer()
{
    if (!isTimerRunnig) {
        scheduleUpdate();
        isTimerRunnig = true;
        initTime = clock();
    }

}

void HelloWorld::stopTimer()
{
    if (isTimerRunnig) {
        unscheduleUpdate();
        isTimerRunnig = false;
    }
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
