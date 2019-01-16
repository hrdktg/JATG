#include "Enemy.h"

Enemy::Enemy(const char *format, int frames, cocos2d::Vec2 pos, cocos2d::Node *s) {
    auto vframe = getAnimation(format, frames);
    auto e1 = cocos2d::Sprite::createWithSpriteFrame(vframe.front());
    e1->setAnchorPoint(cocos2d::Vec2(0,0));
    e1->setPosition(pos);

    auto physicsBody1 = cocos2d::PhysicsBody::createBox(cocos2d::Size(200.0f,200.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody1->setDynamic(false);
    int bmask = 0;

    physicsBody1->setContactTestBitmask(32);

    e1->addComponent(physicsBody1);
    s->addChild(e1);

    auto enemy_anim = cocos2d::Animation::createWithSpriteFrames(vframe, 1.0f/7);
    e1->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(enemy_anim)));
}

/*
   * Bit i is set to 1 when
   * Bit 1 = objType (Player=1, Enemy=0)
   * Bit 2 = isPower
   * Bit 3 = Power A
   * Bit 4 = Power B
   * Bit 5 = Power C
*/
