#include <ui/UIButton.h>
#include "GamePad.h"
#include "Player.h"

GamePad::GamePad(std::string btn1, std::string btn2, std::string btn3, cocos2d::Node *s) {
    auto btn_t = cocos2d::ui::Button::create(btn1,btn1);
    auto btn_s = cocos2d::ui::Button::create(btn2,btn2);
    auto btn_c = cocos2d::ui::Button::create(btn3,btn3);

    btn_c->setPosition(cocos2d::Vec2(72,128));
    btn_s->setPosition(cocos2d::Vec2(245,74));
    btn_t->setPosition(cocos2d::Vec2(244,227));

    btn_t->addTouchEventListener([&,s](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
       CCLOG("TOUCHING TOUCHING");
       switch(type) {
           case cocos2d::ui::Widget::TouchEventType::BEGAN:
               break;
           case cocos2d::ui::Widget::TouchEventType::ENDED:
               shootBullet("bulletp1.png", s);
               break;
       }
    });

    btn_s->addTouchEventListener([&,s](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        CCLOG("TOUCHING TOUCHING");
        switch(type) {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                shootBullet("bulletp2.png", s);
                break;
        }
    });

    btn_c->addTouchEventListener([&,s](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        CCLOG("TOUCHING TOUCHING");
        switch(type) {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                shootBullet("bulletp3.png", s);
                break;
        }
    });

    s->addChild(btn_c);
    s->addChild(btn_s);
    s->addChild(btn_t);
}


void GamePad::shootBullet(std::string sname, cocos2d::Node *s) {
    //420,390
    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(65.0f,81.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0x02);
    physicsBody->setTag(2);

    auto img1 = cocos2d::Sprite::createWithSpriteFrameName(sname);
    img1->setAnchorPoint(cocos2d::Vec2(0,0));
    img1->setPosition(cocos2d::Vec2(420,390));
    cocos2d::MoveBy* action = cocos2d::MoveBy::create(4,cocos2d::Vec2(1530,0));
    img1->runAction(action);

    img1->addComponent(physicsBody);
    s->addChild(img1);
}
