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

    auto pauseBtn = MenuItemImage::create("pause_btn.png","pause_btn.png",CC_CALLBACK_0(GameScene::runPauseScene, this));
    pauseBtn->setAnchorPoint(Vec2(0,0));

    auto menu = Menu::create(pauseBtn, NULL);
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

    this->schedule(schedule_selector(GameScene::runSpawnEnemy),2.0f);
    /*auto spritecache = SpriteFrameCache::getInstance();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    GameObj bg_main("bg_main","bg_main.png",Vec2(0,0),this);
    GameObj player("player","player.png",Vec2(65,350),this);
    //GameObj pauseBtn("pauseBtn","pause_btn.png",Vec2(38,900),this);
    GameObj score_box("score_box","score_box.png",Vec2(1280,860),this);
    //enemy : 1670, 350

    auto frames = getAnimation("enemy_anim%d.png",7); // SpriteFrame*
    auto enemy = Sprite::createWithSpriteFrame(frames.front()); //sprite
    enemy->setAnchorPoint(Vec2(0,0));
    enemy->setPosition(Vec2(1610,350));
    this->addChild(enemy);

    auto enemy_anim = Animation::createWithSpriteFrames(frames, 1.0f/7);
    enemy->runAction(RepeatForever::create(Animate::create(enemy_anim)));
    //this->scheduleUpdate();

    std::vector<cocos2d::Sprite* >hp_player;
    for(int x=0;x<5;x++) {
        hp_player.push_back(Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("heart_player.png")));
        hp_player[x]->setPosition(Vec2(90+x*60,507));
        this->addChild(hp_player[x]);
    }

    std::vector<cocos2d::Sprite* >hp_enemy;
    for(int x=0;x<5;x++) {
        hp_enemy.push_back(Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("heart_enemy.png")));
        hp_enemy[x]->setPosition(Vec2(1610+x*60,760));
        this->addChild(hp_enemy[x]);
    }

    auto btn_t = ui::Button::create("bulletp1.png","bulletp1.png");
    auto btn_s = ui::Button::create("bulletp2.png","bulletp2.png");
    auto btn_c = ui::Button::create("bulletp3.png","bulletp3.png");

    btn_c->setPosition(Vec2(72,128));
    btn_s->setPosition(Vec2(245,74));
    btn_t->setPosition(Vec2(244,227));

    this->addChild(btn_c);
    this->addChild(btn_s);
    this->addChild(btn_t);

    btn_c->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        shootBullet(1);
    });

    //auto pauseBtn_pos = Vec2();

*/

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

/*
void GameScene::update(float dt) {
    Vec2 pos = enemy.getObj()->getPosition();
    enemy.getObj()->setPosition(Vec2(pos.x, pos.y+py));
    py+=vy;

    if(pos.y>400) vy=-1;
    if(pos.y<350) vy=1;
}
*/

inline bool GameScene::getkbit(int num,int k) {
    return (num>>(k-1))&1;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &cont) {
    CCLOG("Collision");

    int nodeA = cont.getShapeA()->getBody()->getContactTestBitmask();
    int nodeB = cont.getShapeB()->getBody()->getContactTestBitmask();

    auto na = cont.getShapeA()->getBody()->getNode();
    auto nb = cont.getShapeB()->getBody()->getNode();

    auto actionRemove = RemoveSelf::create();
    /*
     * if set / not set
     * bit 1 = power
     * bit 2 = pow 1
     * bit 3 = pow 2
     * bit 4 = pow 3
     * bit 5 = player or enemy
     *
     * 5 4 3 2 1
     */
    /*  Check If power strikes power and powers of diff obj (a1&b1) && !(a5&b5)
     *           power strikes player or enemy
     *           power strikes power of same player
     *           power strikes same player or same enemy
     */

    bool an[6];
    bool bn[6];

    for(int x=1;x<=5;x++) an[x]=getkbit(nodeA, x);
    for(int x=1;x<=5;x++) bn[x]=getkbit(nodeA, x);

    bool samePow=false;
    if((an[2]&bn[2]) || (an[3]&bn[3]) || (an[4]&bn[4])) samePow=true;

    //Power Strikes Power
    if(an[1]&bn[1]) {
        //If Powers of different Player
        if(!(an[5]&bn[5])) {
            na->runAction(Sequence::create(actionRemove, nullptr));
            nb->runAction(Sequence::create(actionRemove, nullptr));
            //If same type of power
            if(samePow) {
                Hud::getInstance()->reduceHp(1);
            } else {
                Hud::getInstance()->reduceHp(0);
            }
        }
    }

    /*
    //Power strikes Obj
    else {
        //Power strikes different obj then its parent
        if(!(an[5]&bn[5])) {
            //Remove Power from scene
            if(an[1]) {
                na->runAction(Sequence::create(actionRemove, nullptr));
                //Power strikes player
                if(bn[5]) {
                    Hud::getInstance()->reduceHp(0);
                }
                else {
                    //Power strikes enemy
                }
            }
            else {
                nb->runAction(Sequence::create(actionRemove, nullptr));
                if(an[5]) {
                    Hud::getInstance()->reduceHp(0);
                }
                else {
                    //Power strikes enemy
                }
            }
        }
    }
     */
/*
    cocos2d::log("%d %d collides", nodeA, nodeB);
    //label->setString(std::to_string(nodeA)+" "+std::to_string(nodeB));

    if(nodeA == nodeB && na!=nb && (nodeA!=1 && nodeA!=2)) {
        //Both are powers A player and B enemy
        CCLOG("Destroy them Decrease HP of enemy");
        label->setString("Destroy them Decrease HP of enemy");

        Hud::getInstance()->reduceHp(1);
        na->runAction(Sequence::create(actionRemove, nullptr));
        nb->runAction(Sequence::create(actionRemove, nullptr));
    }
    else if(nodeA>=4 && nodeB>=4) {
        //Both are diff powers
        //Reduce Hp of player
        Hud::getInstance()->reduceHp(0);

        na->runAction(Sequence::create(actionRemove, nullptr));
        nb->runAction(Sequence::create(actionRemove, nullptr));
    }
    else if((nodeB>=4) && (nodeB<=8)) {
        if(nodeA==1) {
            //Power strike player
            //Pow is nodeB and Player is nodeA
            //Reduce Hp of player
           // Hud::getInstance()->reduceHp(0);

            //nb->runAction(Sequence::create(actionRemove, nullptr));
            label->setString("Destroy them Decrease HP of player");
        }
        else if(nodeA==2) {
            //Power strike Enemy
            //Pow is nodeB and Player is nodeA
            //Enemy Shield Activates
            //nb->runAction(Sequence::create(actionRemove, nullptr));
            label->setString("Destroy them head on");
        }
    }
*/
    return true;
}

void GameScene::runSpawnEnemy(float dt) {
    CCLOG("SPAWNING");

    cocos2d::MoveBy* action = cocos2d::MoveBy::create(4,cocos2d::Vec2(-1530,0));

    int type = random(1,3);

    auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(65.0f,81.0f), cocos2d::PhysicsMaterial(1.0f, 1.0f, 1.0f));
    physicsBody->setDynamic(false);
    //1,2,3
    int bmask = 0;
    setBit(bmask, 1);

    setBit(bmask, type+1);

    physicsBody->setContactTestBitmask(bmask); //4,6,8
    physicsBody->setTag(1);

    std::string sname = "bullete" + std::to_string(type) + ".png";
    auto img1 = cocos2d::Sprite::createWithSpriteFrameName(sname);
    img1->setAnchorPoint(Vec2(0,0));
    img1->setPosition(Vec2(1679,390));
    img1->runAction(action);

    img1->addComponent(physicsBody);
    this->addChild(img1);
}