#include "TutScene.h"
#include "Circle.h"

Scene* TutScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TutScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TutScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.



	return true;
}


void TutScene::createCircleHowto()
{
	auto redCircle = Circle::create("Red");
	redCircle->setPosition(Point(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 2));
	redCircle->setName("redCircleTut");
	redCircle->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 1.1f), ScaleTo::create(0.5f, 1.0f), nullptr)));
	redCircle->setCircleText("Sky");
	this->addChild(redCircle);

	auto skyCircle = Circle::create("Sky");
	skyCircle->setPosition(Point(origin.x + (visibleSize.width / 3) * 2, origin.y + visibleSize.height / 2));
	skyCircle->setName("skyCircleTut");
	skyCircle->setCircleText("Red");
	this->addChild(skyCircle);

	auto tapTut = Sprite::create("Play/Tap.png");
	tapTut->setName("tapTut");
	tapTut->setPosition(Point(redCircle->getPositionX() - 100, redCircle->getPositionY()));
	tapTut->setOpacity(0);
	tapTut->runAction(Sequence::create(DelayTime::create(1.0f), FadeIn::create(1.0f), nullptr));
	this->addChild(tapTut);

	//this->stopAllActions();
	auto redarrow = Sprite::create("Play/RedArrow.png");
	this->addChild(redarrow);
	redarrow->setName("redArrow");
	redarrow->setPosition(0 + 480 / 2, 800 / 2 + 100);
	redarrow->setScale(0.8f);
	//redarrow->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.5f, 1.1f), ScaleTo::create(0.25f, 1.0f)));
	redarrow->setVisible(false);

	auto skyarrow = Sprite::create("Play/SkyArrow.png");
	this->addChild(redarrow);
	skyarrow->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 100);
	skyarrow->setScale(0.8f);
	//skyarrow->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.5f, 1.1f), ScaleTo::create(0.25f, 1.0f)));
	skyarrow->setVisible(false);
	skyarrow->setName("skyArrow");
}
