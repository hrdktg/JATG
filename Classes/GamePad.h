#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#include <2d/CCAnimation.h>
#include <2d/CCActionInterval.h>
#include <2d/CCSprite.h>
#include "GameObj.h"

class GamePad : public GameObj {
private:
    cocos2d::Sprite *img;
    std::vector<cocos2d::Vec2> lst;
    std::vector<cocos2d::Sprite* > bull;
public:
    GamePad(std::string btn1, std::string btn2, std::string btn3, cocos2d::Node *s);

    void shootBullet(std::string sname,int bmask, cocos2d::Node *s);

    inline int getBit(int num,int k) {
        return (num>>(k-1)) & 1;
    }
    inline void setBit(int &num, int k) {
        num |=(1<<(k-1));
    }
};

#endif //__GAMEPAD_H__