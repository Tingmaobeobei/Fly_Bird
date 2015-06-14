#include "HelloWorldScene.h"
#include "SceneOne.h"
#include"GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SimpleAudioEngine::getInstance()->preloadEffect("die.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("hit.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("point.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("swooshing.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("wing.mp3");

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Start_Scene", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
  //  this->addChild(label, 1);

    // add "HelloWorld" splash screen"
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist");
    auto background = Sprite::createWithSpriteFrameName("bg.png");

    // position the sprite on the center of the screen
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
	this->addChild(background, 0);
    




	auto bird = Sprite::createWithSpriteFrameName("bird1.png");
	

	auto animation = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		char szName[100] = { 0 };
		sprintf(szName, "bird%d.png", i);
		auto _sprite = Sprite::createWithSpriteFrameName(szName);
		animation->addSpriteFrame(_sprite->getSpriteFrame());				
	}
	animation->setDelayPerUnit(1.5f / 14.0f);

	animation->setRestoreOriginalFrame(true);

	auto action = Animate::create(animation);

	auto swing = MoveBy::create( 0.5f,Vec2(0, 10));
	
	bird->runAction(RepeatForever::create(action));
 
	bird->runAction(RepeatForever::create(Sequence::create(swing,swing->reverse(),NULL)));
	bird->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bird, 10);

	auto flappybird = Sprite::createWithSpriteFrameName("bird_logo.png");
	flappybird->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+3*flappybird->getContentSize().height));
	this->addChild(flappybird, 100);
	  
	/*auto land1 = Sprite::createWithSpriteFrameName("land.png");
	land1->setPosition(Vec2(visibleSize.width / 2 + origin.x,visibleSize.height/2-background->getPositionY()+land1->getContentSize().height));
	this->addChild(land1, 100);
	auto land1move = MoveBy::create(3.0f, Vect(land1->getContentSize().width, 0));
	


	auto land2 = Sprite::createWithSpriteFrameName("land.png");
	land2->setPosition(Vec2(visibleSize.width / 2 + origin.x-land1->getContentSize().width, visibleSize.height / 2 - background->getPositionY() + land1->getContentSize().height));
	this->addChild(land2, 100);
	auto land2move = MoveBy::create(3.0f, Vect(land2->getContentSize().width, 0));

	 
		land1->runAction(land1move);
		land2->runAction(land2move);*/
	land1 = Sprite::createWithSpriteFrameName("land.png");
	land1->setAnchorPoint(Point::ZERO);
	land1->setPosition(Point::ZERO);
	this->addChild(land1, 10);  //置于最顶层  
	land2 = Sprite::createWithSpriteFrameName("land.png");
	land2->setAnchorPoint(Point::ZERO);
	land2->setPosition(Point::ZERO);
	this->addChild(land2, 10);
	//this->schedule(schedule_selector(HelloWorld::scrollLand), 0.01f);
	//land = Land::create();
	//land->setPosition(Vec2(visibleSize.width, visibleSize.height));
	//this->addChild(land, 100);
	auto start_bt = Sprite::createWithSpriteFrameName("start_btn.png");
	auto pressed_bt = Sprite::createWithSpriteFrameName("start_btn_pressed.png");
	auto closeItem = MenuItemSprite::create(
		start_bt,
		pressed_bt,
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 - background->getPositionY() +3* closeItem->getContentSize().height));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 101);
		//this->scheduleUpdate();//使用update()函数来更新
		this->schedule(schedule_selector(HelloWorld::myupdate));//使用自定义函数来更新
		
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
	auto scene = GameScene::createScene();
	auto transition = TransitionFade::create(1, scene);
	// run
	Director::getInstance()->replaceScene(transition);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

/*void HelloWorld::scrollLand(float dt)
{
	this->land1->setPositionX(this->land1->getPositionX() - 2.0f);
	this->land2->setPositionX(this->land1->getPositionX() + this->land1->getContentSize().width - 2.0f);

	if (this->land2->getPositionX() == 0) {
		this->land1->setPositionX(0);
	}

}

void HelloWorld::update(float delta)
{
	int posLand1 = land1->getPositionX();
	int posLand2 = land2->getPositionX();

	int speed = 1;

	posLand1 -= speed;
	posLand2 -= speed;

	

	auto landsize = land2->getContentSize();

	if (posLand1 < -landsize.width / 2+142)
	{
		posLand2 = landsize.width / 2;
		posLand1 = landsize.width + landsize.width / 2;
	}

	if (posLand2 < -landsize.width / 2+142)
	{
		posLand1 = landsize.width / 2;
		posLand2 = landsize.width + landsize.width / 2;
	}
	land1->setPositionX(posLand1);
	land2->setPositionX(posLand2);
}*/

void HelloWorld::myupdate(float delta)
{
	int posLand1 = land1->getPositionX();
	int posLand2 = land2->getPositionX();

	int speed = 1;

	posLand1 -= speed;
	posLand2 -= speed;



	auto landsize = land2->getContentSize();

	if (posLand1 < -landsize.width / 2 + 142)
	{
		posLand2 = 0;
		posLand1 = landsize.width + 0;
	}

	if (posLand2 < -landsize.width / 2 + 142)
	{
		posLand1 = 0;
		posLand2 = landsize.width + 0;
	}
	land1->setPositionX(posLand1);
	land2->setPositionX(posLand2);
}