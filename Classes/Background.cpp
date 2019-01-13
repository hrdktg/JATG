#include "Background.h"

Background::Background(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s) {
    img = cocos2d::Sprite::create(sname);
    img->setAnchorPoint(cocos2d::Vec2(0, 0));
    img->setPosition(pos);
    s->addChild(img);

}