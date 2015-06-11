#include "MenuScene.h"
#include "InfoScene.h"
#include <SimpleAudioEngine.h>

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
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
	playItem = MenuItemImage::create("Menu/PlayBtn.png", "Menu/PlayBtn.png", CC_CALLBACK_1(MenuScene::menuPlayCallback, this));
	playItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 370));

	optionItem = MenuItemImage::create("Menu/HowtoBtn.png", "Menu/HowtoBtn.png", CC_CALLBACK_1(MenuScene::menuSoundCallback, this));
	optionItem->setPosition(Vec2(303, 230));

	infoItem = MenuItemImage::create("Menu/InfoBtn.png", "Menu/InfoBtn.png", CC_CALLBACK_1(MenuScene::menuInfoCallback, this));
	infoItem->setPosition(Vec2(217, 163));

	exitItem = MenuItemImage::create("Menu/ExitBtn.png", "Menu/ExitBtn.png", CC_CALLBACK_1(MenuScene::menuExitCallback, this));
	exitItem->setPosition(Vec2(175, 247));

	auto menu = Menu::create(playItem,optionItem, infoItem, exitItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	auto title = Sprite::create("Menu/Title.png");
	title->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 3) * 2);
	this->addChild(title);

	return true;
}

void MenuScene::menuPlayCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	playItem->runAction(Sequence::create(ScaleTo::create(0.25f,1.1f), ScaleTo::create(0.25f,1.0f), nullptr));
	auto Scene = PlayScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInR::create(0.25f, Scene));
}
void MenuScene::menuSoundCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	optionItem->runAction(Sequence::create(ScaleTo::create(0.25f,1.1f),ScaleTo::create(0.25f,1),nullptr));
}
void MenuScene::menuInfoCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	auto infoscene = InfoScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInR::create(0.25f, infoscene));
	infoItem->runAction(Sequence::create(ScaleTo::create(0.25f,1.1f),ScaleTo::create(0.25f,1),nullptr));
}
void MenuScene::menuExitCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	auto func = CallFunc::create([=]
	{
		Director::getInstance()->end();
	});

	exitItem->runAction(Sequence::create(ScaleTo::create(0.2f,1.1f),ScaleTo::create(0.5f,1), func, nullptr));
}