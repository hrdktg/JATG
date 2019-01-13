#ifndef __SCOREBOX_H__
#define __SCOREBOX_H__

#include <2d/CCAnimation.h>
#include <2d/CCActionInterval.h>
#include <2d/CCSprite.h>
#include "GameObj.h"

class ScoreBox : public GameObj {
private:
    cocos2d::Sprite *img;
public:
    ScoreBox();
    ScoreBox(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s);
};

#endif //__SCOREBOX_H__