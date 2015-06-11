#include "PlayScene.h"
#include "OverScene.h"
#include "PauseScene.h"
#include <SimpleAudioEngine.h>

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
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	scoreLabel = Label::createWithTTF("", "fonts/Roboto-Condensed.ttf", 50);
	scoreLabel->setPosition(origin.x + visibleSize.width - 50, origin.y + visibleSize.height - 50);
	scoreLabel->setColor(Color3B::BLACK);
	this->addChild(scoreLabel);

	_currentLevel = 0;
	_selectedCircles = 0;
	_isWin = false;
	_isPaused = false;

	_timer = 0.0f;
	_totalTime = 8.0f;

	auto progressBG = Sprite::create("Objects/ProgressBG.png");
	progressBG->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + progressBG->getContentSize().height / 2));
	this->addChild(progressBG);

	_progress = ProgressTimer::create(Sprite::create("Objects/Progress.png"));
	_progress->setType(ProgressTimerType::BAR);
	_progress->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + _progress->getContentSize().height / 2));
	_progress->setBarChangeRate(Vec2(1, 0));
	_progress->setPercentage(0);
	_progress->setMidpoint(Vec2(0.0, 0.0f));
	this->addChild(_progress);

	createCircle();

	this->scheduleUpdate();

	//Listener
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//Pause Btn
	auto pauseBtn = MenuItemImage::create("Play/PauseBtn.png", "Play/PauseBtn.png", CC_CALLBACK_0(PlayScene::pauseGame, this));
	pauseBtn->setPosition(origin.x + 50, origin.y + visibleSize.height - 50);

	auto menu = Menu::create(pauseBtn, nullptr);
	menu->setPosition(0, 0);
	this->addChild(menu);

	return true;
}

void PlayScene::update(float dt)
{
	_timer += dt;
	_progress->setPercentage(100 - ((_timer / _totalTime) * 100.0f));

	if (_timer > _totalTime)
	{
		log("THUA THUA THUA...");
		this->pause();
		auto overscene = OverScene::createScene(_currentLevel);
		Director::getInstance()->replaceScene(TransitionMoveInR::create(0.25f, overscene));
	}

	//if (_currentLevel > 1)
	{
		_isWin = this->checkWin();
		if (_isWin)
		{
			_isWin = false;
			createCircle();
		}
	}
}

void PlayScene::setSelectedCircle(Circle* circle)
{
	if (_selectedCircles < 1)
	{
		_circleList.push_back(circle);
		_selectedCircles++;
	}
	else
	{
		std::string temp = circle->getCircleName();
		circle->changeTexture(_circleList[0]->getCircleName());
		_circleList[0]->changeTexture(temp);

		//if (_currentLevel > 1)
			this->checkWin();

		_selectedCircles = 0;
		_circleList.clear();
	}
		
}

void PlayScene::resetSelectedCircle()
{
}

int PlayScene::getCurrentLevel()
{
	return _currentLevel;
}

bool PlayScene::onToucBegan(Touch* touch, Event* event)
{
	return true;
}

std::string PlayScene::randomColor()
{
	int color = random(0, 6);

	std::string colorPattern[7] = { "Red", "Green", "Blue", "Orange", "Pink", "Purple", "Yellow"};

	return colorPattern[color];
}

void PlayScene::createCircle()
{
	_circleList.clear();
	_colorList.clear();
	removeAllCircle();
	int numCircle = 2;

	_timer = 0.0f;

	//Tang so hinh tron
	if (_currentLevel < 2)
	{
		numCircle = 2;
	}
	else if (_currentLevel < 5)
	{
		numCircle = 3;
	}
	else if (_currentLevel < 10)
	{
		numCircle = 4;
		_totalTime = 10.0f;
	}
	else if (_currentLevel < 15)
	{
		numCircle = 5;
		_totalTime = 15.0f;
	}
	else if (_currentLevel < 20)
	{
		numCircle = 6;
		_totalTime = 20.0f;
	}

	for (int i = 0; i < numCircle; i++)
	{
		bool canpush;
		do
		{
			auto color = randomColor();
			canpush = true;
			for (int j = 0; j < _colorList.size(); j++)
			{
				if (_colorList[j] == color)
				{
					canpush = false;
					break;
				}
			}
			if (canpush)
				_colorList.push_back(color);
		} while (canpush == false);
	}

	std::vector<std::string> colorText;

	colorText = _colorList;
	for (int i = colorText.size() - 1; i > 0; i--)
	{
		int j = colorText.size() - 1;
		do
		{
			std::swap(colorText[i], colorText[random(0, j)]);
		} while (colorText[i] == _colorList[i]);
	}

	for (int j = 0; j < _colorList.size(); j++)
	{
		auto circle = Circle::create(_colorList[j]);
		circle->setCircleText(colorText[j]);
		circle->setOpacity(0);
		
		circle->runAction(Sequence::create(DelayTime::create(0.05f), FadeIn::create(0.25f), nullptr));
		this->addChild(circle);

		circle->randomPosition();
	}

	_currentLevel++;
	_timer = 0;
	_progress->setPercentage(0);
	scoreLabel->setString(String::createWithFormat("%d", _currentLevel)->getCString());
}

bool PlayScene::checkWin()
{
	auto children = this->getChildren();

	for (auto it = children.begin(); it != children.end(); ++it)
	{
		if (Circle* c = dynamic_cast<Circle*>(*it))
		{
			c->checkMatch();
			if (!c->isMatched())
			{
				return false;
			}
		}
	}

	return true;
}

void PlayScene::removeAllCircle()
{
	auto children = this->getChildren();

	for (auto it = children.begin(); it != children.end(); ++it)
	{
		if (Circle* c = dynamic_cast<Circle*>(*it))
		{
			auto removeFunc = CallFunc::create([=]{
				c->removeFromParent();
			});

			//if (_currentLevel <= 1)
			{
				c->runAction(Sequence::create(ScaleTo::create(0.2f, c->getScale() + 0.2f), ScaleTo::create(0.2f, 0.0f), removeFunc, NULL));
			}
			
		}
	}
}

void PlayScene::pauseGame()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");
	if (_isPaused == false)
	{
		this->pause();
		auto paused = PauseScene::createScene();
		Director::getInstance()->pushScene(TransitionMoveInL::create(0.25f, paused));
	}
	else
	{
		this->resume();
	}
	
}