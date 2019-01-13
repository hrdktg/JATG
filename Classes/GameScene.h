#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "GameObj.h"


class GameScene : public cocos2d::Scene
{
private:
    //GameObj enemy;
    int px = 0 ,py = 0;
    int vx = 0, vy = 1;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    void runPauseScene();

    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
    //virtual void update(float dt);

    void shootBullet(int bullet_t);
};

#endif // __GAMESCENE_H__
