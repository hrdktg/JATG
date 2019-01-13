#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#include <2d/CCAnimation.h>
#include <2d/CCActionInterval.h>
#include <2d/CCSprite.h>
#include "GameObj.h"

class GamePad : public GameObj {
private:
    cocos2d::Sprite *img;
public:
    GamePad();
    GamePad(std::string btn1, std::string btn2, std::string btn3, cocos2d::Node *s);
};

#endif //__GAMEPAD_H__