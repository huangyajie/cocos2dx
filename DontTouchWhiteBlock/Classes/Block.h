//
//  Block.h
//  DontTouchWhiteBlock
//
//  Created by Mac on 15/7/4.
//
//

#ifndef __DontTouchWhiteBlock__Block__
#define __DontTouchWhiteBlock__Block__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;


class Block :public CCSprite
{
public:
    bool initWithArgs(ccColor3B color,CCSize size,std::string text,float fontsize ,ccColor3B textColor);
    static Block* create(ccColor3B color,CCSize size,std::string text,float fontsize,ccColor3B textColor);
    
    void removeBlock();
    
    void setRow(int row);
    int getRow();
    
    static std::vector<Block*>* getBlocks();
    void moveDown();
    void clean();
    
private:
    static std::vector<Block*> *blocks;
    int index;
    

};

#endif /* defined(__DontTouchWhiteBlock__Block__) */
