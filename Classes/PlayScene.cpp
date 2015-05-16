#include "PlayScene.h"
#include "Circle.h"

Scene* PlayScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PlayScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	//TEST
	for (int i = 0; i < 10; i++)
	{
		auto circle = Circle::create("Objects/RedCircle_Normal.png");
		this->addChild(circle);
		circle->setName(String::createWithFormat("%d", i)->getCString());
	}

	return true;
}
