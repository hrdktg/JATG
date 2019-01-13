#include "Player.h"



Player::Player(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s) {
    img = getFromSheet(sname);
    img->setAnchorPoint(cocos2d::Vec2(0,0));
    img->setPosition(pos);
    s->addChild(img);

    for(int x=0;x<5;x++) {
        hp_player.push_back(getFromSheet("heart_player.png"));
        hp_player[x]->setPosition(cocos2d::Vec2(90+x*60,507));
        s->addChild(hp_player[x]);
    }
}