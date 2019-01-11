#include "Splash.h"
#include "MainMenu.h"
#include "GameObj.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Splash::createScene()
{
    auto scene = Splash::create();
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Splash::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
//    this->setColor(Color3B(230,211,169));
//    this->setOpacity(255);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pos=Vec2(visibleSize.width/2, visibleSize.height/2);
    auto pos1=Vec2(pos.x+10, pos.y+10);
    GameObj splash_scr("splash_scr","splash_scr.png",pos,this);

    //std::string str1 = std::to_string(frameSize.height);
    //std::string str2 = std::to_string(frameSize.width);
    //auto myLabel = Label::createWithSystemFont(str1+","+str2, "Arial", 32);
    //myLabel->setColor(Color3B(255,255,0));
    //myLabel->setPosition(pos);
    //this->addChild(myLabel);
    this->scheduleOnce(schedule_selector(Splash::runMainMenu), 2.0f);
    return true;
}

void Splash::runMainMenu(float dt) {
    auto MainMenuScene = MainMenu::create();
    Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenuScene, Color3B(48,56,44)));
}

void Splash::menuCloseCallback(Ref* pSender)
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
