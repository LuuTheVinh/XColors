#include "IntroScene.h"


Scene* IntroScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IntroScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
	auto introBG = Sprite::create("LogoTeamX.png");
	introBG->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(introBG);

	this->scheduleOnce(schedule_selector(IntroScene::gotoMenuScene), 2.0f);
    
    return true;
}

void IntroScene::gotoMenuScene(float dt)
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInR::create(0.25f, menuscene));
}
