#ifndef __SCOREBOX_H__
#define __SCOREBOX_H__

#include <2d/CCAnimation.h>
#include <2d/CCActionInterval.h>
#include <2d/CCSprite.h>
#include "GameObj.h"

class ScoreBox : public GameObj {
private:
    cocos2d::Sprite *img;
    bool lastPlayer = 0; //0->Enemy, 1->Player whoever got the last hit correct
    cocos2d::Label *curScore, *score_label;
    int curStreak;

    ScoreBox() { }
    ///std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s)
    static ScoreBox* sc_instance;
public:
    void updateScore(bool isP1);

    static ScoreBox* getInstance() {
        if(!sc_instance) {
            sc_instance = new ScoreBox();
        }
        return sc_instance;
    }

    void init(std::string sname);
    void showScore(cocos2d::Vec2 pos, cocos2d::Node *s);
    void showScore(cocos2d::Vec2 pos, cocos2d::Node *s, bool isMidAnchor);
};

#endif //__SCOREBOX_H__