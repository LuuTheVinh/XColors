#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "cocos2d.h"

USING_NS_CC;

class Circle : public Sprite
{
public:
	void setCircleText(std::string text);
	void setCircleName(std::string text);
	std::string getCircleText();
	std::string getCircleName();
	void changeTexture(std::string type);
	bool isSelected();
	bool isMatched();

	virtual bool init();
	virtual void onEnter();
	
	bool onTouchBegan(Touch* touch, Event* event);
	
	static Circle* create(std::string filename);
	void checkMatch();
	void randomPosition();

private:
	std::string _circleText;
	std::string _circleName;

	Label* _colorLabel;
	Label* shadowLabel;

	Size _visibleSize;
	Vec2 _origin;

	bool _isSelected;
	bool _isMatched;

	
	
};


#endif //__CIRCLE_H__
