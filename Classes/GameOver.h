#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__
//#include "Box2D/Box2D.h"
#include "cocos2d.h"

USING_NS_CC;
class GameOver : public cocos2d::Layer
{
	void scrollLand(float dt);

	Sprite *land1;
	Sprite *land2;
	//b2World *world;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	virtual void update(float delta);

	void myupdate(float delta);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuReStartCallback(cocos2d::Ref* pSender);

	void menuGameOverCallback(cocos2d::Ref* pSender);

	//void scrollLand(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);
};

#endif // __HELLOWORLD_SCENE_H__
