#include <ui/UIButton.h>
#include "GamePad.h"
#include "Player.h"
/*
   * if set / not set
   * bit 1 = power
   * bit 2 = pow 1
   * bit 3 = pow 2
   * bit 4 = pow 3
   * bit 5 = player or enemy
   *
   * 5 4 3 2 1
   */

GamePad::GamePad(std::string btn1, std::string btn2, std::string btn3, cocos2d::Node *s) {
    auto btn_t = cocos2d::ui::Button::create(btn1,btn1);
    auto btn_s = cocos2d::ui::Button::create(btn2,btn2);
    auto btn_c = cocos2d::ui::Button::create(btn3,btn3);

    btn_c->setPosition(cocos2d::Vec2(72,128));
    btn_s->setPosition(cocos2d::Vec2(245,74));
    btn_t->setPosition(cocos2d::Vec2(244,227));


    btn_t->addTouchEventListener([&,s](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
       CCLOG("TOUCHING TOUCHING");
        int bmask = 0;
        bmask|=1<<5;
        bmask|=1<<1;
        bmask|=1<<2;
        //setBit(bmask, 5);
        //setBit(bmask, 1);
        //setBit(bmask, 2);
       switch(type) {
           case cocos2d::ui::Widget::TouchEventType::BEGAN:
               break;
           case cocos2d::ui::Widget::TouchEventType::ENDED:
               shootBullet("bulletp1.png", bmask,  s);
               break;
       }
    });

    btn_s->addTouchEventListener([&,s](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        CCLOG("TOUCHING TOUCHING");
        int bmask = 0;
        bmask|=1<<5;
        bmask|=1<<1;
        bmask|=1<<3;
        //setBit(bmask, 5);
        //setBit(bmask, 1);
        //setBit(bmask, 3);
        switch(type) {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                shootBullet("bulletp2.png", bmask, s);
                break;
        }
    });

    btn_c->addTouchEventListener([&,s](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        CCLOG("TOUCHING TOUCHING");
        int bmask = 0;
        bmask|=1<<5;
        bmask|=1<<1;
        bmask|=1<<4;
        //setBit(bmask, 5);
        //setBit(bmask, 1);
        //setBit(bmask, 4);
        switch(type) {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                shootBullet("bulletp3.png", bmask, s);
                break;
        }
    });

    s->addChild(btn_c);
    s->addChild(btn_s);
    s->addChild(btn_t);
}


void GamePad::shootBullet(std::string sname,int bmask, cocos2d::Node *s) {
    //420,390
    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(400.0f,390.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(bmask);
    physicsBody->setTag(2);

    auto img1 = cocos2d::Sprite::createWithSpriteFrameName(sname);
    img1->setAnchorPoint(cocos2d::Vec2(0,0));
    img1->setPosition(cocos2d::Vec2(420,390));
    cocos2d::MoveBy* action = cocos2d::MoveBy::create(4,cocos2d::Vec2(1530,0));
    img1->runAction(action);

    img1->addComponent(physicsBody);
    s->addChild(img1);
}
