#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <2d/CCAnimation.h>
#include <2d/CCActionInterval.h>
#include <2d/CCSprite.h>
#include <2d/CCSpriteFrameCache.h>
#include "GameObj.h"

class Player : public GameObj {
private:
    cocos2d::Sprite *img;
    std::vector<cocos2d::Sprite* >hp_player;
public:
    Player(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s);
};

#endif //__PLAYER_H__