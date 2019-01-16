#include "Player.h"



Player::Player(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s) {
    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(65.0f,81.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody->setDynamic(false);
    int bmask = 0;
    setBit(bmask, 1);

    physicsBody->setContactTestBitmask(bmask);
    physicsBody->setTag(1);

    img = getFromSheet(sname);
    img->setAnchorPoint(cocos2d::Vec2(0,0));
    img->setPosition(pos);

    img->addComponent(physicsBody);

    s->addChild(img);
}
/*
  * Bit i is set to 1 when
  * Bit 1 = objType (Player=1, Enemy=0)
  * Bit 2 = isPower
  * Bit 3 = Power A
  * Bit 4 = Power B
  * Bit 5 = Power C
*/