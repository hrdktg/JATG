#include "MainMenu.h"
#include "GameObj.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Background.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pos=Vec2(visibleSize.width/2, visibleSize.height/4);
    auto pos1=Vec2(pos.x+10, pos.y+10);

    auto bg_main = cocos2d::Sprite::create("bg_main.png");
    auto bg_curtain_bg = cocos2d::Sprite::create("bg_curtain_bg.png");
    bg_curtain_bg->setAnchorPoint(Vec2(0,0));
    bg_curtain_bg->setPosition(Vec2(0,0));

    auto bg_curtain = cocos2d::Sprite::create("bg_curtain.png");
    bg_curtain->setAnchorPoint(Vec2(0,0));
    bg_curtain->setPosition(Vec2(0,0));

    auto credit1 = cocos2d::Sprite::create("credit1.png");
    credit1->setAnchorPoint(Vec2(0,0));
    credit1->setPosition(Vec2(0,0));

    auto github_icon = cocos2d::Sprite::create("github_icon.png");
    github_icon->setAnchorPoint(Vec2(0,0));
    github_icon->setPosition(Vec2(visibleSize.width-github_icon->getContentSize().width-50,50));


    auto gTitle = cocos2d::Sprite::create("title.png");
    gTitle->setAnchorPoint(Vec2(0, 0));
    gTitle->setPosition(Vec2(visibleSize.width/2-gTitle->getContentSize().width/2, visibleSize.height-gTitle->getContentSize().height));

    auto playBtn = MenuItemImage::create("play_btn.png","play_btn.png",CC_CALLBACK_0(MainMenu::runGameScene, this));
    auto optBtn = MenuItemImage::create("options_btn.png","options_btn.png",CC_CALLBACK_0(MainMenu::runOptScene, this));
    auto creditsBtn = MenuItemImage::create("credits_btn.png","credits_btn.png",CC_CALLBACK_0(MainMenu::runGameScene, this));

    auto menu = Menu::create(playBtn, optBtn, creditsBtn, NULL);

    menu->alignItemsVerticallyWithPadding(visibleSize.height / 10);
    bg_main->setPosition(cocos2d::Vec2(visibleSize.width/2, visibleSize.height/2));

    this->addChild(bg_curtain_bg);
    this->addChild(bg_curtain);
    this->addChild(credit1);
    this->addChild(github_icon);

    //this->addChild(bg_main);
    this->addChild(gTitle);
    this->addChild(menu);

    return true;
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MainMenu::runOptScene() {

}

void MainMenu::runGameScene() {
    auto scene = GameScene::create();
    Director::getInstance()->replaceScene(scene);
}