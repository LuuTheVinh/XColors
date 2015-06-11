#include "InfoScene.h"
#include "MenuScene.h"
#include <SimpleAudioEngine.h>

Scene* InfoScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = InfoScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool InfoScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	auto score = Sprite::create("Over/ScoreCircleBG.png");
	score->setPosition(visibleSize.width / 2, 470);
	this->addChild(score);

	menuItem = MenuItemImage::create("Pause/MenuBtn.png", "Pause/MenuBtn.png", CC_CALLBACK_1(InfoScene::menuMenuCallback, this));
	menuItem->setPosition(Vec2(440, 760));

	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);


	return true;
}

void InfoScene::menuMenuCallback(Ref* penter)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	auto func = CallFunc::create([=]
	{
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	menuItem->runAction(Sequence::create(ScaleTo::create(0.2f,1.1f),ScaleTo::create(0.5f,1), func, nullptr));
}