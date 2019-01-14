#include "Enemy.h"

Enemy::Enemy(const char *format, int frames, cocos2d::Vec2 pos, cocos2d::Node *s) {
    auto vframe = getAnimation(format, frames);
    auto e1 = cocos2d::Sprite::createWithSpriteFrame(vframe.front());
    e1->setAnchorPoint(cocos2d::Vec2(0,0));
    e1->setPosition(pos);

    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(65.0f,81.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0x08);
    physicsBody->setTag(3);

    e1->addComponent(physicsBody);

    s->addChild(e1);

    auto enemy_anim = cocos2d::Animation::createWithSpriteFrames(vframe, 1.0f/7);
    e1->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(enemy_anim)));


    for(int x=0;x<5;x++) {
        hp_enemy.push_back(cocos2d::Sprite::createWithSpriteFrameName("heart_enemy.png"));
        hp_enemy[x]->setPosition(cocos2d::Vec2(1610+x*60,760));
        s->addChild(hp_enemy[x]);
    }
}

