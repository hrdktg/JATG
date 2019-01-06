#include "GameScene.h"
#include "GameObj.h"
#include "SimpleAudioEngine.h"
#include "PauseScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();

    auto layer = GameScene::create();

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
bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pos=Vec2(visibleSize.width/2, visibleSize.height/2);

    auto pauseBtn = MenuItemImage::create("pauseBtn.png","pauseBtn.png",CC_CALLBACK_0(GameScene::runPauseScene, this));
    auto btnSize =pauseBtn->getContentSize();
    //pauseBtn->setPosition(Vec2(btnSize,btnSize));

    auto menu = Menu::create(pauseBtn, NULL);
    menu->setPosition(Vec2(btnSize.width,visibleSize.height-btnSize.height));
    this->addChild(menu);

    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
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

void GameScene::runPauseScene() {
    auto scene = PauseScene::create();
    Director::getInstance()->replaceScene(scene);
}