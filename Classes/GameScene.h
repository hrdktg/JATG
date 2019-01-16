#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "GameObj.h"
#include "Enemy.h"
#include "Hud.h"


class GameScene : public cocos2d::Scene
{
private:
    //GameObj enemy;
    int px = 0 ,py = 0;
    int vx = 0, vy = 1;
    cocos2d::Label *label = cocos2d::Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

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

    inline bool getkbit(int num,int k);
    inline void setBit(int &num, int k) {
        num |=1<<k-1;
    }
};


#endif // __GAMESCENE_H__
