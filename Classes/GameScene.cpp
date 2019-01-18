#include "GameScene.h"
#include "GameObj.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "PauseScene.h"
#include "Enemy.h"
#include "Player.h"
#include "GamePad.h"
#include "ScoreBox.h"
#include "Background.h"
#include <string>


USING_NS_CC;


Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -9));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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

    Scene::initWithPhysics();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("jatg.plist");

    auto i1 = Sprite::createWithSpriteFrameName("player.png");
    i1->setAnchorPoint(Vec2(0,0));
    i1->setPosition(Vec2(0,0));

    Background bg_main("bg_main.png", Vec2(0,0), this);
    ScoreBox score_box("score_box.png", Vec2(1280,860), this);

    Player player1("player.png", Vec2(65,350), this);
    Enemy enemy1("enemy_anim%d.png", 7, Vec2(1610,350), this);

    GamePad pad("bulletp1.png", "bulletp2.png", "bulletp3.png", this);

    auto hud = Hud::getInstance();
    hud->setSceneRef(this);
    hud->initFullHpBar();

    initPauseMenu();
    auto pauseBtn = MenuItemImage::create("pause_btn.png","pause_btn.png",CC_CALLBACK_0(GameScene::runPauseScene, this));
    //auto resumeBtn = MenuItemImage::create("pause_btn.png","pause_btn.png",CC_CALLBACK_0(GameScene::resumeScene, this));
    pauseBtn->setAnchorPoint(Vec2(0,0));
    //resumeBtn->setAnchorPoint(Vec2(0,0));
    //resumeBtn->setPosition(Vec2(100,100));
    //resumeBtn->setRotation(0.5f);

    auto menu = Menu::create(pauseBtn,  NULL);
    menu->setPosition(Vec2(38,900));
    this->addChild(menu);

    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    label->setAnchorPoint(Vec2(0,0));
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);

    this->schedule(schedule_selector(GameScene::runSpawnEnemy), 2.0f);

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

void GameScene::initPauseMenu() {
    menu_bg = cocos2d::Sprite::create("menu_bg.png");
    soundBtn = cocos2d::Sprite::create("soundBtn.png");

    resumeBtn = cocos2d::ui::Button::create("resumeBtn.png", "resumeBtn.png");
    resumeBtn->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        menu_bg->setVisible(false);
        soundBtn->setVisible(false);
        resumeBtn->setVisible(false);

        menu_bg->pause();
        soundBtn->pause();
        resumeBtn->pause();
        Director::getInstance()->resume();
    });

    menu_bg->setAnchorPoint(cocos2d::Vec2(0,0));
    soundBtn->setAnchorPoint(cocos2d::Vec2(0,0));
    resumeBtn->setAnchorPoint(cocos2d::Vec2(0,0));

    menu_bg->setPosition(cocos2d::Vec2(0,0));
    resumeBtn->setPosition(cocos2d::Vec2(36,908));
    soundBtn->setPosition(cocos2d::Vec2(494,51));

    this->addChild(menu_bg,1);
    this->addChild(resumeBtn,1);
    this->addChild(soundBtn,1);

    menu_bg->setVisible(false);
    resumeBtn->setVisible(false);
    soundBtn->setVisible(false);

    menu_bg->pause();
    resumeBtn->pause();
    soundBtn->pause();
}

void GameScene::runPauseScene() {
    if(!Director::getInstance()->isPaused()) {
        Director::getInstance()->pause();

        menu_bg->setVisible(true);
        soundBtn->setVisible(true);
        resumeBtn->setVisible(true);

        menu_bg->resume();
        soundBtn->resume();
        resumeBtn->resume();
    }
}

/*
void GameScene::update(float dt) {
    Vec2 pos = enemy.getObj()->getPosition();
    enemy.getObj()->setPosition(Vec2(pos.x, pos.y+py));
    py+=vy;

    if(pos.y>400) vy=-1;
    if(pos.y<350) vy=1;
}
*/

bool GameScene::onContactBegin(cocos2d::PhysicsContact &cont) {
    CCLOG("Collision");

    int A = cont.getShapeA()->getBody()->getContactTestBitmask();
    int B = cont.getShapeB()->getBody()->getContactTestBitmask();

    int powPow = getBit(A,2) & getBit(B,2);
    int sameObj = (int)(getBit(A,1)==getBit(B,1));
    int samePow = (A>>2) & (B>>2);

    auto nodeA = cont.getShapeA()->getBody()->getNode();
    auto nodeB = cont.getShapeB()->getBody()->getNode();

    label->setString(std::to_string(A)+","+std::to_string(B));
    if(!sameObj) {
        auto actionRemove = RemoveSelf::create();

        if(powPow) {
            if(samePow) {
                nodeA->runAction(Sequence::create(actionRemove, nullptr));
                nodeB->runAction(Sequence::create(actionRemove, nullptr));

                Hud::getInstance()->reduceHp(0);
            }
            else {
                nodeA->runAction(Sequence::create(actionRemove, nullptr));
                nodeB->runAction(Sequence::create(actionRemove, nullptr));

                Hud::getInstance()->reduceHp(1);
            }
        } else {
            if(A==1) {
                //Power strikes Player
                nodeB->runAction(Sequence::create(actionRemove, nullptr));
                Hud::getInstance()->reduceHp(1);
            }
            else if(A==32) {
                CCLOG("STRIKING ENEMY WITH POWER");
                //Power Strikes Enemy
                nodeB->runAction(Sequence::create(actionRemove, nullptr));
            }
            else if(B==1) {
                //Power strikes Player
                Hud::getInstance()->reduceHp(1);
                nodeA->runAction(Sequence::create(actionRemove, nullptr));
            }
            else if(B==32) {
                CCLOG("STRIKING ENEMY WITH POWER");
                //Power Strikes Enemy
                nodeA->runAction(Sequence::create(actionRemove, nullptr));
            }
        }
    }

    return true;
}

void GameScene::runSpawnEnemy(float dt) {
    CCLOG("SPAWNING");

    cocos2d::MoveBy* action = cocos2d::MoveBy::create(4,cocos2d::Vec2(-1530,0));

    int type = random(1,3);

    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(100.0f,100.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody->setDynamic(false);
    //1,2,3
    int bmask = 0;
    setBit(bmask, 2);
    setBit(bmask, type+2); //set 3, 4 or 5 bit for respective Power

    physicsBody->setContactTestBitmask(bmask);
    physicsBody->setTag(1);

    std::string sname = "bullete" + std::to_string(type) + ".png";
    auto img1 = cocos2d::Sprite::createWithSpriteFrameName(sname);
    img1->setAnchorPoint(Vec2(0,0));
    img1->setPosition(Vec2(1679,390));
    img1->runAction(action);

    img1->addComponent(physicsBody);
    this->addChild(img1);
}

/*
   * Bit i is set to 1 when
   * Bit 1 = objType (Player=1, Enemy=0)
   * Bit 2 = isPower
   * Bit 3 = Power A
   * Bit 4 = Power B
   * Bit 5 = Power C
*/