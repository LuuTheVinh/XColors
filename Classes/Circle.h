#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "cocos2d.h"

USING_NS_CC;

class Circle : public Sprite
{
public:
	void setText(std::string text);
	virtual bool init();
	virtual void onEnter();
	
	static Circle* create(std::string filename);

private:
	std::string circleText;
	std::string circleName;

	Size visibleSize;
	Vec2 origin;

	void randomPosition();
};


#endif //__CIRCLE_H__
