#include "Circle.h"

Circle* Circle::create(std::string filename)
{
	Circle* circle = new Circle();

	if (circle && circle->initWithFile(filename))
	{
		circle->init();
		circle->autorelease();
		return circle;
	}

	CC_SAFE_DELETE(circle);
	return nullptr;
}

bool Circle::init()
{
	this->setName("Circle");

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//Random
	//this->setScale(random(0.5f, 1.0f));


	return true;
}

void Circle::onEnter()
{
	Sprite::onEnter();

	randomPosition();
}

void Circle::randomPosition()
{
	

	//Xet vi tri do da co chua
	//...
	auto layer = this->getParent();
	auto childs = layer->getChildren();
	bool canRandom = true;
	
	do
	{
		canRandom = true;

		auto x = random(0 + this->getContentSize().width / 2, visibleSize.width - this->getContentSize().width / 2);
		auto y = random(100 + this->getContentSize().height / 2, visibleSize.height - 100 - this->getContentSize().width / 2);

		for (auto it = childs.begin(); it != childs.end(); ++it)
		{
			if (Circle* c = dynamic_cast<Circle*>(*it))
			{
				if (c == this) continue;

				auto rect = Rect(c->getPosition().x, c->getPosition().y, c->getBoundingBox().size.width * c->getScale(), c->getBoundingBox().size.height * c->getScale());

				if (c->getBoundingBox().containsPoint(Point(x, y)))
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

}