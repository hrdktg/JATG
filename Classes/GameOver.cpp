#include "GameOver.h"
#include "GameObj.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Hud.h"
#include "ui/CocosGUI.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    auto scene = Scene::create();

    auto layer = GameOver::create();

    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    if(1 == Hud::getInstance()->getWonPlayerId()) {
        playerWon();
    }
    else {
        enemyWon();
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto retryBtn = MenuItemImage::create("retry_btn.png","retry_btn.png",CC_CALLBACK_0(GameOver::retryScene, this));
    auto mainMenuBtn = MenuItemImage::create("main_menu_btn.png", "main_menu_btn.png",CC_CALLBACK_0(GameOver::runMainMenu, this));

    auto menu = Menu::create(retryBtn, mainMenuBtn, NULL);
    menu->setAnchorPoint(cocos2d::Vec2(0,0));
    menu->setPosition(cocos2d::Vec2(786,230));
    menu->alignItemsHorizontallyWithPadding(visibleSize.width/4);
    this->addChild(menu);

    return true;
}

void GameOver::menuCloseCallback(Ref* pSender)
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

void GameOver::runMainMenu() {
    auto mmsc = MainMenu::create();
    cocos2d::Director::getInstance()->replaceScene(mmsc);

}

void GameOver::retryScene() {
    auto rsc = GameScene::create();
    cocos2d::Director::getInstance()->replaceScene(rsc);
}

void GameOver::playerWon() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = cocos2d::Label::createWithTTF("You Won", "fonts/Marker Felt.ttf",72);
    auto pos = cocos2d::Vec2(visibleSize.width/2, visibleSize.height/2);

    label->setPosition(pos);
    this->addChild(label);

}

void GameOver::enemyWon() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = cocos2d::Label::createWithTTF("You Loose", "fonts/Marker Felt.ttf",72);
    auto pos = cocos2d::Vec2(visibleSize.width/2, visibleSize.height/2);
    label->setPosition(pos);

    this->addChild(label);
}