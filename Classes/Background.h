#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <2d/CCAnimation.h>
#include <2d/CCActionInterval.h>
#include <2d/CCSprite.h>
#include <2d/CCSpriteFrameCache.h>
#include "GameObj.h"

class Background : public GameObj {
private:
    cocos2d::Sprite *img;

public:
    Background();
    Background(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s);
};

#endif //__BACKGROUND_H__