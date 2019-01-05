#ifndef __GAMEOBJ_SCENE_H__
#define __GAMEOBJ_SCENE_H__

#include <string>
#include <iostream>
#include <2d/CCSprite.h>

class GameObj {
private:
    std::string name;
    bool isContainer;
    int nObj;
    int x,y,width,height;
    std::map<std::string,GameObj> objArr;

    cocos2d::Sprite* img;

public:
    GameObj() {
        name = "";
        isContainer = false;
        x = y = width = height = 0;
        nObj = 0;
    }

    GameObj(std::string name, std::string loc, cocos2d::Vec2 pos, Splash *s) {
        this->name = name;

        img = cocos2d::Sprite::create(loc);
        img->setPosition(pos);

        s->addChild(img);
    }

    virtual int Size() {
        return nObj;
    }

    virtual void setName(std::string n) {
        name = n;
    }

    //n is the number of objects contained.
    virtual void makeContainer(int n) {
        isContainer = true;
    }

    virtual void setDim(int a,int b,int w,int h) {
        x = a;
        y = b;
        width = w;
        height = h;
    }

    virtual void addObj(std::string objName, GameObj tmp) {
        objArr[objName] = tmp;
        nObj++;
    }

    //
    virtual void loadSprite(std::string sprite_loc, cocos2d::Vec2 pos) {
        img = cocos2d::Sprite::create(sprite_loc);

        img->setPosition(pos);
    }

    virtual cocos2d::Node * getSprite() {
        return img;
    }
};


#endif // __GAMEOBJ_SCENE_H__