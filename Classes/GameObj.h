#ifndef __GAMEOBJ_SCENE_H__
#define __GAMEOBJ_SCENE_H__

#include <string>
#include <iostream>
#include <2d/CCSprite.h>
#include <2d/CCSpriteFrameCache.h>

class GameObj {
private:

    cocos2d::Sprite* img;
    cocos2d::SpriteFrameCache *spritecache = cocos2d::SpriteFrameCache::getInstance();


public:
    GameObj() {

    }

    GameObj(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s) {

        img = cocos2d::Sprite::create(sname);
        img->setAnchorPoint(cocos2d::Vec2(0,0));
        img->setPosition(pos);

        s->addChild(img);
    }


    virtual cocos2d::Node *getSprite() {
        return img;
    }

    //Supports at most 100 frames.
    virtual cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count) {
        auto spritecache = cocos2d::SpriteFrameCache::getInstance();
        cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
        char str[100];

        for(int i=1;i<=count;i++) {
            sprintf(str, format, i);
            animFrames.pushBack(spritecache->getSpriteFrameByName(str));
        }
        return animFrames;
    }

    virtual cocos2d::SpriteFrameCache* getSpritecache() {
        return spritecache;
    }

    virtual cocos2d::Sprite* getFromSheet(std::string sname) {
        return cocos2d::Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName(sname));
    }

};


#endif // __GAMEOBJ_SCENE_H__