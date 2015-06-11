#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Circle.h"

USING_NS_CC;

class PlayScene : public cocos2d::LayerColor
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(PlayScene);

	void setSelectedCircle(Circle* circle);
	void resetSelectedCircle();
	int getCurrentLevel();

	bool onToucBegan(Touch* touch, Event* event);

private:
	std::vector<std::string> _colorList;
	std::vector<Circle*> _circleList;
	std::string randomColor();

	Size visibleSize;
	Vec2 origin;

	int _selectedCircles;
	bool _isWin;
	float _timer;
	float _totalTime;
	
	Label* scoreLabel;
	bool _isPaused;

	ProgressTimer* _progress;

	int _currentLevel;
	void createCircle();
	int myrandom(int i) { return std::rand() % i; }
	bool checkWin();
	void removeAllCircle();
	void pauseGame();
	
};

#endif // __INTRO_SCENE_H__
