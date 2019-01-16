#include "Player.h"



Player::Player(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s) {
    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(65.0f,81.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody->setDynamic(false);
    int bmask = 0;
    setBit(bmask, 5);

    physicsBody->setContactTestBitmask(bmask);
    physicsBody->setTag(1);

    img = getFromSheet(sname);
    img->setAnchorPoint(cocos2d::Vec2(0,0));
    img->setPosition(pos);

    img->addComponent(physicsBody);

    s->addChild(img);
}
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