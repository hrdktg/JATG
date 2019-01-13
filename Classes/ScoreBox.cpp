#include "ScoreBox.h"

ScoreBox::ScoreBox(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s) {
    img = getFromSheet(sname);
    img->setAnchorPoint(cocos2d::Vec2(0, 0));
    img->setPosition(pos);
    s->addChild(img);
}