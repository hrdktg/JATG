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

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("jatg.plist");

    Player player("player.png", Vec2(65,350), this);
    Enemy enemy("enemy_anim%d.png", 7, Vec2(1610,350), this);

    Background bg_main("bg_main.png", Vec2(0,0), this);
    ScoreBox score_box("score_box.png", Vec2(1280,860), this);

    GamePad pad("bulletp1.png", "bulletp2.png", "bulletp3.png", this);

    auto pauseBtn = MenuItemImage::create("pause_btn.png","pause_btn.png",CC_CALLBACK_0(GameScene::runPauseScene, this));
    pauseBtn->setAnchorPoint(Vec2(0,0));

    auto menu = Menu::create(pauseBtn, NULL);
    menu->setPosition(Vec2(38,900));
    this->addChild(menu);


    /*auto spritecache = SpriteFrameCache::getInstance();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    GameObj bg_main("bg_main","bg_main.png",Vec2(0,0),this);
    GameObj player("player","player.png",Vec2(65,350),this);
    //GameObj pauseBtn("pauseBtn","pause_btn.png",Vec2(38,900),this);
    GameObj score_box("score_box","score_box.png",Vec2(1280,860),this);
    //enemy : 1670, 350

    auto frames = getAnimation("enemy_anim%d.png",7);
    auto enemy = Sprite::createWithSpriteFrame(frames.front());
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

void GameScene::shootBullet(int bullet_t) {
    auto spritecache = SpriteFrameCache::getInstance();
    if(bullet_t==1) {
        auto bullet = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("bulletp1.png"));
        bullet->setPosition(Vec2(440,389));
        this->addChild(bullet);
    }
}