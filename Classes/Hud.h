#ifndef __HUD_H__
#define __HUD_H__

#include <2d/CCAnimation.h>
#include <2d/CCActionInterval.h>
#include <2d/CCSprite.h>
#include <2d/CCSpriteFrameCache.h>
#include "GameObj.h"

class Hud : public GameObj {
private:
    std::vector<cocos2d::Sprite* >hp_bars[2];

    static Hud *hud_instance;
    cocos2d::Node* sc;

    static int hp[2]; //Player is 1 and Enemy is 0

    Hud() {};

public:
    static Hud *getInstance();
    void initFullHpBar();
    void setSceneRef(cocos2d::Node *s);
    void reduceHp(bool obj);
    void showPauseMenu(cocos2d::Node *s);

};

#endif //__HUD_H__