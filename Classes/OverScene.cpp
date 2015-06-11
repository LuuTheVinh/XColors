#include "OverScene.h"
#include "PlayScene.h"
#include "MenuScene.h"
#include <SimpleAudioEngine.h>

Scene* OverScene::createScene(int score)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();


	// 'layer' is an autorelease object
	auto layer = OverScene::create();
	layer->setLevel(score);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool OverScene::init()
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
	score->setPosition(visibleSize.width/2, 470);
	this->addChild(score);

	shareItem = MenuItemImage::create("Over/ShareBtn.png", "Over/ShareBtn.png", CC_CALLBACK_0(OverScene::menuShareCallback, this));
	shareItem->setPosition(Vec2(300, 310));

	againItem = MenuItemImage::create("Over/AgainBtn.png", "Over/AgainBtn.png", CC_CALLBACK_0(OverScene::menuAgainCallback, this));
	againItem->setPosition(Vec2(185, 330));

	menuItem = MenuItemImage::create("Pause/MenuBtn.png", "Pause/MenuBtn.png", CC_CALLBACK_0(OverScene::menuMenuCallback, this));
	menuItem->setPosition(Vec2(215, 260));

	auto menu = Menu::create(againItem, menuItem, shareItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);


	LevelLable = Label::createWithTTF("", "fonts/Roboto-Condensed.ttf", 60);
	LevelLable->setColor(Color3B::WHITE);
	LevelLable->setAlignment(TextHAlignment::CENTER);
	LevelLable->setPosition(origin.x + visibleSize.width / 2, origin.y + score->getPositionY() + LevelLable->getContentSize().height / 2 + 40);
	this->addChild(LevelLable);

	bestScore = Label::createWithTTF("", "fonts/Roboto-Condensed.ttf", 50);
	bestScore->setColor(Color3B::WHITE);
	bestScore->setAlignment(TextHAlignment::CENTER);
	bestScore->setPosition(origin.x + visibleSize.width / 2, origin.y + score->getPositionY() - bestScore->getContentSize().height / 2 - 35);
	this->addChild(bestScore);

	return true;
}

void OverScene::menuAgainCallback()
{	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	auto func = CallFunc::create([=]
	{
		auto scene = PlayScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	againItem->runAction(Sequence::create(ScaleTo::create(0.2f,1.1f),ScaleTo::create(0.05f,1), func, nullptr));
}
void OverScene::menuMenuCallback()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	auto func = CallFunc::create([=]
	{
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	menuItem->runAction(Sequence::create(ScaleTo::create(0.2f,1.1f),ScaleTo::create(0.05f,1), func, nullptr));

}
void OverScene::menuShareCallback()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	shareItem->runAction(Sequence::create(ScaleTo::create(0.2f,1.1f),ScaleTo::create(0.5f,1), nullptr));
}
void OverScene::setLevel(int level)
{
	int Level = level;
	auto userdefault=UserDefault::getInstance();
	auto HeighLevel=userdefault->getIntegerForKey("HEIGHSCORE", 0);


	LevelLable->setString(String::createWithFormat("%d", Level)->getCString());

	if (HeighLevel != 0) bestScore->setString(String::createWithFormat("BEST: %d", HeighLevel)->getCString());

	if(Level> HeighLevel)
	{
		userdefault->setIntegerForKey("HEIGHSCORE",Level);
	}
	userdefault->flush();
}