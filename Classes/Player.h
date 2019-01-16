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
    std::vector<cocos2d::Sprite* >hp_player;    //Store the hearts sprite depicting the current hp of player.
    std::vector<cocos2d::Sprite* >bullets;      //Store the location of bullets currently on the screen.


public:
    Player(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s);

    inline int getBit(int num,int k) {
        return (num>>(k-1)) & 1;
    }
    inline void setBit(int &num, int k) {
        num |=(1<<(k-1));
    }
   // static void shootBullet(std::string sname, cocos2d::Node *s);
};

#endif //__PLAYER_H__