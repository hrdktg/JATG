#include <2d/CCActionInstant.h>
#include "Hud.h"
#include "GameOver.h"

Hud* Hud::hud_instance = NULL;
int Hud::hp[] = {5, 5};

Hud *Hud::getInstance() {

    if(!hud_instance) {
        hud_instance = new Hud;
    }
    return hud_instance;

}

void Hud::reduceHp(bool obj) {
    //Player -> 1
    hp[obj]--;
    if(hp[obj] <= 0) {
        wonPlayerId = obj;
        //Go to Game Over Scene
        auto goversc = GameOver::createScene();
        cocos2d::Director::getInstance()->replaceScene(goversc);

    }
    else {

        cocos2d::Sprite* tmp = hp_bars[obj][hp[obj]];
        auto actionRemove = cocos2d::RemoveSelf::create();
        tmp->runAction(cocos2d::Sequence::create(actionRemove, nullptr));

    }
}

void Hud::setSceneRef(cocos2d::Node* s) {
    sc = s;
}

void Hud::initFullHpBar() {
    hp[0] = 5;
    hp[1] = 5;
    hp_bars[0].clear();
    hp_bars[1].clear();

    for(int x=0;x<hp[0];x++) {
        hp_bars[0].push_back(cocos2d::Sprite::createWithSpriteFrameName("heart_enemy.png"));
        hp_bars[0][x]->setPosition(cocos2d::Vec2(1610+x*60,760));
        sc->addChild(hp_bars[0][x]);
    }

    for(int x=0;x<hp[1];x++) {
        hp_bars[1].push_back(getFromSheet("heart_player.png"));
        hp_bars[1][x]->setPosition(cocos2d::Vec2(90+x*60,507));
        sc->addChild(hp_bars[1][x]);
    }
}

