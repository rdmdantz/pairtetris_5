#include "GameTitleScene.h"
#include "InGameScene.h"

USING_NS_CC;

Scene* CSMenu::createScene()
{
	CCLog("CSMenuScene :: CreateScene");

    auto scene = Scene::create();
	auto layer = CSMenu::create();
    scene->addChild(layer);

    return scene;
}

CSMenu::CSMenu()
{
	CCLOG("CSMenu()");
}

CSMenu::~CSMenu()
{
	CCLOG("~CSMenu()");
}


bool CSMenu::init()
{

	CCLOG("CSMenu::init()");
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	CCSprite *pSpr_bg = CCSprite::create("menu-bg.jpg");
	pSpr_bg->setAnchorPoint(Point(0, 1));
	pSpr_bg->setPositionY(visibleSize.height);
	addChild(pSpr_bg);

	auto startItem = MenuItemImage::create("title/Play-0.png", "title/Play-1.png", CC_CALLBACK_1(CSMenu::menuStartCallback, this));
	startItem->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + startItem->getContentSize().height / 2 + 200));
	auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	auto quitItem = MenuItemImage::create("title/Quit-0.png", "title/Quit-1.png", CC_CALLBACK_1(CSMenu::menuQuitCallback, this));
	quitItem->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + quitItem->getContentSize().height / 2 + 40));

	auto menu4 = Menu::create(quitItem, NULL);
	menu4->setPosition(Point::ZERO);
	this->addChild(menu4, 1);

    
    
    return true;
}


void CSMenu::menuStartCallback(Object* pSender)
{
	CCLog("Play");
	Scene *pScene = TransitionSplitRows::create(1.0, CSInGame::createScene());
	Director::getInstance()->replaceScene(pScene);

}


void CSMenu::menuQuitCallback(Object* pSender)
{
	CCLog("Bey Bey~");
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}