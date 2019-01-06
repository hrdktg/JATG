#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);

    void Resume();
    void Retry();
    void runMainMenu();
};

#endif // __GAMEOVER_H__
