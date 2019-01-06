#include "PauseScene.h"
#include "GameObj.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    auto scene = Scene::create();

    auto layer = PauseScene::create();

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
bool PauseScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto resumeBtn = MenuItemImage::create("resumeBtn.png","resumeBtn.png",CC_CALLBACK_0(PauseScene::Resume,this));
    auto retryBtn = MenuItemImage::create("retryBtn.png","retryBtn.png",CC_CALLBACK_0(PauseScene::Retry,this));
    auto menuBtn = MenuItemImage::create("menuBtn.png","menuBtn.png",CC_CALLBACK_0(PauseScene::runMainMenu,this));

    auto menu = Menu::create(resumeBtn, retryBtn, menuBtn, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height/4);
    this->addChild(menu);

    return true;
}

void PauseScene::menuCloseCallback(Ref* pSender)
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

void PauseScene::Resume() {

}

void PauseScene::Retry() {

}

void PauseScene::runMainMenu() {

}
