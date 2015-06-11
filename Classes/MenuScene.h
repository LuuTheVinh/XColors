#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "PlayScene.h"

USING_NS_CC;

class MenuScene : public cocos2d::LayerColor
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	cocos2d::MenuItemImage* playItem;
	cocos2d::MenuItemImage* optionItem;
	cocos2d::MenuItemImage* infoItem;
	cocos2d::MenuItemImage* exitItem;
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	// implement the "static create()" method manually
	
	void menuPlayCallback(Ref* pSender);
	void menuSoundCallback(Ref* pSender);
	void menuInfoCallback(Ref* pSender);
	void menuExitCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(MenuScene);

};

#endif // __MENU_SCENE_H__
