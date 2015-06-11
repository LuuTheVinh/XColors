#include "PauseScene.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include <SimpleAudioEngine.h>

Scene* PauseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
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
	// 2. Pause scene

	resumeItem = MenuItemImage::create("Pause/ResumeBtn.png", "Pause/ResumeBtn.png", CC_CALLBACK_1(PauseScene::menuResumeCallback, this));
	resumeItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	
	menuItem = MenuItemImage::create("Pause/MenuBtn.png", "Pause/MenuBtn.png", CC_CALLBACK_1(PauseScene::menuMenuCallback,this));
	menuItem->setPosition(Vec2(325, 310));	
	
	againItem = MenuItemImage::create("Pause/AgainBtn.png", "Pause/AgainBtn.png", CC_CALLBACK_1(PauseScene::menuAgainCallback, this));
	againItem->setPosition(Vec2(visibleSize.width / 2, 275));
	
	musicItem = MenuItemImage::create("Pause/ShareBtn.png", "Pause/ShareBtn.png", CC_CALLBACK_1(PauseScene::menuMusicCallback, this));
	musicItem->setPosition(Vec2(155, 310));
	
	auto menu = Menu::create(resumeItem, menuItem, againItem, musicItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void PauseScene::menuResumeCallback(Ref* pSender)
{ 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	auto func = CallFunc::create([=]
	{
		//auto scene = PlayScene::createScene();
		Director::getInstance()->popScene();
	});

	resumeItem->runAction(Sequence::create(ScaleTo::create(0.2f,1.1f),ScaleTo::create(0.05f,1), func, nullptr));
}

void PauseScene::menuMenuCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	auto func = CallFunc::create([=]
	{
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	menuItem->runAction(Sequence::create(ScaleTo::create(0.2f,1.1f),ScaleTo::create(0.05f,1), func, nullptr));
}
void PauseScene::menuAgainCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	auto func = CallFunc::create([=]
	{
		auto scene = PlayScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	againItem->runAction(Sequence::create(ScaleTo::create(0.2f,1.1f),ScaleTo::create(0.05f,1), func, nullptr));

}
void PauseScene::menuMusicCallback(Ref* pSender)
{

}