#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <2d/CCAnimation.h>
#include <2d/CCActionInterval.h>
#include <2d/CCSprite.h>
#include <2d/CCSpriteFrameCache.h>
#include "GameObj.h"

class Enemy : public GameObj {
private:
    std::vector<cocos2d::Sprite* >hp_enemy;

public:
    //enemy("enemy_anim%d.png", 7, Vec2(1610,350), this);
    Enemy(const char *format, int frames, cocos2d::Vec2 pos, cocos2d::Node *s);
};

#endif //__ENEMY_H__