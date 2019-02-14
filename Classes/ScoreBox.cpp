#include <2d/CCLabel.h>
#include "ScoreBox.h"

ScoreBox* ScoreBox::sc_instance = NULL;

void ScoreBox::init(std::string sname) {
    img = getFromSheet(sname);
    img->setAnchorPoint(cocos2d::Vec2(0, 0));
    //s->addChild(img);

    curStreak = 0;

    score_label = cocos2d::Label::createWithTTF("Score", "fonts/ZCOOL.ttf",47);
    curScore = cocos2d::Label::createWithTTF("00000", "fonts/ZCOOL.ttf", 72);

    score_label->setAnchorPoint(cocos2d::Vec2(0,0));
    curScore->setAnchorPoint(cocos2d::Vec2(0,0));

    //score_label->setPosition(cocos2d::Vec2(pos.x+50, pos.y+40));
    //curScore->setPosition(cocos2d::Vec2(pos.x+300, pos.y+30));

    score_label->setColor(cocos2d::Color3B(227, 219, 219));
    curScore->setColor(cocos2d::Color3B(227, 219, 219));

    //s->addChild(score_label);
    //s->addChild(curScore);
}

void ScoreBox::showScore(cocos2d::Vec2 pos, cocos2d::Node *s) {
    img->setPosition(pos);
    s->addChild(img);

    score_label->setPosition(cocos2d::Vec2(pos.x+50, pos.y+40));
    curScore->setPosition(cocos2d::Vec2(pos.x+300, pos.y+30));

    s->addChild(score_label);
    s->addChild(curScore);
}

void ScoreBox::showScore(cocos2d::Vec2 pos, cocos2d::Node *s, bool isMidAnchor) {
    if(isMidAnchor) {
        pos.x = pos.x - img->getContentSize().width/2;
    }
    img->setPosition(pos);
    s->addChild(img);

    score_label->setPosition(cocos2d::Vec2(pos.x+50, pos.y+40));
    curScore->setPosition(cocos2d::Vec2(pos.x+300, pos.y+30));

    s->addChild(score_label);
    s->addChild(curScore);
}

void ScoreBox::updateScore(bool isP1) {
    CCLOG("Updating Score");
    if(isP1==1 && lastPlayer==1) {
        curStreak++;
    }
    else {
        curStreak = 1;
    }
    lastPlayer = isP1;

    if(isP1==0) return;

    int cscore = std::stoi(curScore->getString());
    cscore = (cscore*curStreak)+1;
    CCLOG(std::to_string(cscore).c_str()," is cscore");

    std::string cscore_str = std::to_string(cscore);
    CCLOG(cscore_str.c_str(), " is cscore_str");
    cscore_str.insert(cscore_str.begin(), 5-cscore_str.length(), '0');
    curScore->setString(cscore_str);
}