#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "GameObj.h"
#include "Enemy.h"
#include "Hud.h"
#include "ui/CocosGUI.h"


class GameScene : public cocos2d::Scene
{
private:
    //GameObj enemy;
    int px = 0 ,py = 0;
    int vx = 0, vy = 1;
    cocos2d::Label *label = cocos2d::Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    cocos2d::Sprite* menu_bg = nullptr;
    cocos2d::Sprite* soundBtn = nullptr;
    cocos2d::ui::Button* resumeBtn = nullptr;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    void runPauseScene();
    void runSpawnEnemy(float dt);

    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
    //virtual void update(float dt);

    bool onContactBegin(cocos2d::PhysicsContact &cont);

    inline int getBit(int num,int k) {
        return (num>>(k-1)) & 1;
    }
    inline void setBit(int &num, int k) {
        num |=(1<<(k-1));
    }

    void initPauseMenu();
};


#endif // __GAMESCENE_H__
