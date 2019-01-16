#include "Enemy.h"

Enemy::Enemy(const char *format, int frames, cocos2d::Vec2 pos, cocos2d::Node *s) {
    auto vframe = getAnimation(format, frames);
    auto e1 = cocos2d::Sprite::createWithSpriteFrame(vframe.front());
    e1->setAnchorPoint(cocos2d::Vec2(0,0));
    e1->setPosition(pos);

    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(165.0f,181.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0);
    physicsBody->setTag(3);

    e1->addComponent(physicsBody);

    s->addChild(e1);

    auto enemy_anim = cocos2d::Animation::createWithSpriteFrames(vframe, 1.0f/7);
    e1->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(enemy_anim)));

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
