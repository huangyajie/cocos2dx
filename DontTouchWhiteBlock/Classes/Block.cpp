//
//  Block.cpp
//  DontTouchWhiteBlock
//
//  Created by Mac on 15/7/4.
//
//

#include "Block.h"


std::vector<Block*>* Block:: blocks = new std::vector<Block*>();

bool Block::initWithArgs(ccColor3B color, cocos2d::CCSize size, std::string text, float fontsize,ccColor3B textColor)
{
    CCSprite::init();
    
    index = 0;
    
    //图形
    setContentSize(size);
    setAnchorPoint(ccp(0,0));
    setTextureRect(CCRect(0,0,size.width,size.height));
    setColor(color);
    
    //文字
    auto l = CCLabelTTF::create(text.c_str(),"Consolas",fontsize);
//    l->setText(textColor);
    l->setColor(textColor);
    l->setPosition(ccp(size.width/2,size.height/2));
    
    addChild(l);
    
    
    
    
    return true;
}

void Block::setRow(int row)
{
    index = row;
}

int Block::getRow()
{
    return index;
}

std::vector<Block*>* Block::getBlocks()
{
    return Block::blocks;
}


Block* Block::create(ccColor3B color, cocos2d::CCSize size, std::string text, float fontsize,ccColor3B textColor)
{
    Block* block = new Block();
    block->initWithArgs(color, size, text,fontsize,textColor);
    blocks->push_back(block);
    block->autorelease();
    return block;
}


void Block::removeBlock()
{
    removeFromParent();
    
    
    std::vector<Block*>::iterator it = blocks->begin();
    while (it != blocks->end()) {
        if(*it == this)
        {
            CCLog("clean");
            blocks->erase(it);
            break;
        }
        it ++;
    }

    
}
void Block::clean()
{
    if(index < 0)
        removeBlock();
}

void Block::moveDown()
{
    this->index --;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    runAction(CCSequence::create(CCMoveTo::create(0.1,ccp(getPositionX(),visibleSize.height/4 *index)),CCCallFunc::create(this,callfunc_selector(Block::clean)),NULL));

}



