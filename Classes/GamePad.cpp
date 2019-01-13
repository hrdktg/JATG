#include <ui/UIButton.h>
#include "GamePad.h"

GamePad::GamePad(std::string btn1, std::string btn2, std::string btn3, cocos2d::Node *s) {
    auto btn_t = cocos2d::ui::Button::create(btn1,btn1);
    auto btn_s = cocos2d::ui::Button::create(btn2,btn2);
    auto btn_c = cocos2d::ui::Button::create(btn3,btn3);

    btn_c->setPosition(cocos2d::Vec2(72,128));
    btn_s->setPosition(cocos2d::Vec2(245,74));
    btn_t->setPosition(cocos2d::Vec2(244,227));

    s->addChild(btn_c);
    s->addChild(btn_s);
    s->addChild(btn_t);
}