#include "Circle.h"
#include "PlayScene.h"
#include <SimpleAudioEngine.h>

Circle* Circle::create(std::string type)
{
	Circle* circle = new Circle();
	
	circle->setCircleName(type);

	auto str = "Objects/" + type + "Circle_Normal.png";
	
	if (circle && circle->initWithFile(str))
	{
		circle->init();
		circle->autorelease();
		return circle;
	}

	CC_SAFE_DELETE(circle);
	return nullptr;
}

void Circle::setCircleName(std::string text)
{
	_circleName = text;
}

std::string Circle::getCircleText()
{
	return _circleText;
}

std::string Circle::getCircleName()
{
	return _circleName;
}

void Circle::changeTexture(std::string type)
{
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("Objects/" + type + "Circle_Normal.png");
	this->setTexture(texture);

	_isSelected = false;
	_colorLabel->setColor(Color3B::WHITE);
	shadowLabel->setVisible(true);
	_circleName = type;
}

bool Circle::isSelected()
{
	return _isSelected;
}

void Circle::setCircleText(std::string text)
{
	_circleText = text;

	shadowLabel = Label::createWithTTF(_circleText, "fonts/Roboto-Condensed.ttf", 25);
	shadowLabel->setColor(Color3B::BLACK);
	this->addChild(shadowLabel);

	_colorLabel = Label::createWithTTF(_circleText, "fonts/Roboto-Condensed.ttf", 25);

	this->addChild(_colorLabel);
}

bool Circle::init()
{
	this->setName("Circle");

	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	_isSelected = false;
	_isMatched = false;

	//Listener
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Circle::onTouchBegan, this);
	touchListener->setSwallowTouches(false);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//randomPosition();
	

	return true;
}

void Circle::onEnter()
{
	Sprite::onEnter();
	
	/*if (auto layer = dynamic_cast<PlayScene*>( this->getParent()))
	{
		{
			randomPosition();
		}
	}

	_colorLabel->setPosition(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height / 2);*/
	//Random
	//this->setScale(random(1.0f, 1.5f));

}

bool Circle::isMatched()
{
	return _isMatched;
}


bool Circle::onTouchBegan(Touch* touch, Event* event)
{
	auto touchLocation = touch->getLocation();

	if (this->getBoundingBox().containsPoint(touchLocation))
	{
		if (_isSelected != true)
		{
			_isSelected = true;
			Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("Objects/" + _circleName + "Circle_Selected.png");
			this->setTexture(texture);

			_colorLabel->setColor(Color3B::BLACK);
			shadowLabel->setVisible(false);

			this->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.2f, this->getScale() + 0.1f), ScaleTo::create(0.2f, this->getScale())));

			if (auto layer = dynamic_cast<PlayScene*>(this->getParent()))
			{
				layer->setSelectedCircle(this);
			}
		}
	}
	else
	{
		if (_isSelected != false && !_isMatched)
		{
			_isSelected = false;
			Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("Objects/" + _circleName + "Circle_Normal.png");

			this->setTexture(texture);
			_colorLabel->setColor(Color3B::WHITE);
			shadowLabel->setVisible(true);
		}
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Touch.wav");

	return true;
}

void Circle::randomPosition()
{
	//Xet vi tri do da co chua
	//...
	auto layer = this->getParent();
	auto children = layer->getChildren();
	bool canRandom = true;
	
	do
	{
		canRandom = true;

		auto x = random(0 + this->getContentSize().width / 2, _visibleSize.width - this->getContentSize().width / 2);
		auto y = random(200 + this->getContentSize().height / 2, _visibleSize.height - 150 - this->getContentSize().width / 2);

		for (auto it = children.begin(); it != children.end(); ++it)
		{
			if (Circle* c = dynamic_cast<Circle*>(*it))
			{
				if (c == this || c->getPosition() == Point(0,0)) continue;

				auto rectwidth = (c->getContentSize().width * c->getScale() + this->getContentSize().width * this->getScale()) + 5;
				auto rectheight = (c->getContentSize().height * c->getScale() + this->getContentSize().height * this->getScale()) + 5;

				auto rect = Rect(c->getPosition().x - rectwidth / 2, c->getPosition().y - rectheight / 2, rectwidth, rectheight);

				if (rect.containsPoint(Point(x, y)))
				{
					canRandom = false;
					break;
				}
			}
		}

		if (canRandom)
		{
			this->setPosition(x, y);
			break;
		}
	} while (canRandom == false);

	_colorLabel->setPosition(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height / 2);
	shadowLabel->setPosition(_colorLabel->getPositionX() - 1 , _colorLabel->getPositionY() - 2);
}

void Circle::checkMatch()
{
	if (_circleName == _circleText)
	{
		_isMatched = true;
	}
	else
	{
		_isMatched = false;
	}
}