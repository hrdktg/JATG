#include <ui/UIButton.h>
#include "GamePad.h"
#include "Player.h"

/*
   * Bit i is set to 1 when
   * Bit 1 = objType (Player=1, Enemy=0)
   * Bit 2 = isPower
   * Bit 3 = Power A
   * Bit 4 = Power B
   * Bit 5 = Power C
*/

GamePad::GamePad(std::string btn1, std::string btn2, std::string btn3, cocos2d::Node *s) {
    auto btn_t = cocos2d::ui::Button::create(btn1,btn1);
    auto btn_s = cocos2d::ui::Button::create(btn2,btn2);
    auto btn_c = cocos2d::ui::Button::create(btn3,btn3);

    btn_s->setPosition(cocos2d::Vec2(100,70));
    btn_c->setPosition(cocos2d::Vec2(300,70));
    btn_t->setPosition(cocos2d::Vec2(1740,70));

    btn_t->addTouchEventListener([&,s](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
       CCLOG("TOUCHING TOUCHING");
        int bmask = 0;
        setBit(bmask, 1);
        setBit(bmask, 2);
        setBit(bmask, 3);
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
        setBit(bmask, 1);
        setBit(bmask, 2);
        setBit(bmask, 4);
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
        setBit(bmask, 1);
        setBit(bmask, 2);
        setBit(bmask, 5);
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
    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(100.0f,100.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(bmask);

    auto img1 = cocos2d::Sprite::createWithSpriteFrameName(sname);
    img1->setAnchorPoint(cocos2d::Vec2(0,0));
    img1->setPosition(cocos2d::Vec2(420,390));
    cocos2d::MoveBy* action = cocos2d::MoveBy::create(2,cocos2d::Vec2(1530,0));
    img1->runAction(action);
    img1->addComponent(physicsBody);

    s->addChild(img1);
    //img1->getPhysicsBody()->applyForce(cocos2d::Vec2(100,100));
}
