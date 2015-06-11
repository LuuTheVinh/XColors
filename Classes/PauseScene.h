#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class PauseScene : public cocos2d::LayerColor
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	cocos2d::MenuItemImage *resumeItem, *menuItem, *againItem, *musicItem;
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);

	void menuResumeCallback(Ref* pSender);
	void menuMenuCallback(Ref* pSender);
	void menuAgainCallback(Ref* pSender);
	void menuMusicCallback(Ref* pSender);
};

#endif // __PAUSE_SCENE_H__
