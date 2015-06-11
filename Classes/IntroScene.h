#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

class IntroScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(IntroScene);
private:
	void gotoMenuScene(float dt);
};

#endif // __INTRO_SCENE_H__
