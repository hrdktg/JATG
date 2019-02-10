#include <2d/CCLabel.h>
#include "ScoreBox.h"

ScoreBox::ScoreBox(std::string sname, cocos2d::Vec2 pos, cocos2d::Node *s) {
    img = getFromSheet(sname);
    img->setAnchorPoint(cocos2d::Vec2(0, 0));
    img->setPosition(pos);
    s->addChild(img);

    auto score_label = cocos2d::Label::createWithTTF("Score", "fonts/ZCOOL.ttf",47);
    auto score_txt = cocos2d::Label::createWithTTF("99999", "fonts/ZCOOL.ttf", 72);

    score_label->setAnchorPoint(cocos2d::Vec2(0,0));
    score_txt->setAnchorPoint(cocos2d::Vec2(0,0));

    score_label->setPosition(cocos2d::Vec2(pos.x+50, pos.y+40));
    score_txt->setPosition(cocos2d::Vec2(pos.x+300, pos.y+30));

    score_label->setColor(cocos2d::Color3B(227, 219, 219));
    score_txt->setColor(cocos2d::Color3B(227, 219, 219));

    s->addChild(score_label);
    s->addChild(score_txt);
}