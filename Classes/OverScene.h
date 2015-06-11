#ifndef __OVER_SCENE_H__
#define __OVER_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class OverScene : public cocos2d::LayerColor
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int score);
	cocos2d::MenuItemImage *againItem, *menuItem, *shareItem;
	cocos2d::Label* LevelLable; 
	cocos2d::Label* bestScore;
	cocos2d::Label* HeighLevelLable;
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(OverScene);

	void menuAgainCallback();
	void menuShareCallback();
	void menuMenuCallback();
	void setLevel(int level);
private:
	int _level;
};

#endif // __OVER_SCENE_H__
