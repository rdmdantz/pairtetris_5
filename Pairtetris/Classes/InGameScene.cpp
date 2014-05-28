#include "InGameScene.h"
#include "BlockManager.h"
USING_NS_CC;

Scene* CSInGame::createScene()
{
    auto scene = Scene::create();
	auto layer = CSInGame::create();
    scene->addChild(layer);
    
	return scene;
}

bool CSInGame::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    

	

	

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	
   
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(CSInGame::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

   
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    auto sprite_BG = Sprite::create("menu-bg.jpg");
	sprite_BG->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite_BG, 0);

	auto sprite_FR = Sprite::create("gameframe.png");
	sprite_FR->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite_FR, 0);

	//auto block_red = Sprite::create("block.png");
	//block_red->setPosition(Point(visibleSize.width / 2 + origin.x - 150, visibleSize.height / 2 + origin.y));
	//block_red->setColor(cocos2d::Color3B(245, 5, 5));
	//this->addChild(block_red, 1);

	//auto block_blue = Sprite::create("block.png");
	//block_blue->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//block_blue->setColor(cocos2d::Color3B(5, 245, 5));
	//this->addChild(block_blue, 1);

	//auto block_green = Sprite::create("block.png");
	//block_green->setPosition(Point(visibleSize.width / 2 + origin.x + 150, visibleSize.height / 2 + origin.y));
	//block_green->setColor(cocos2d::Color3B(5, 5, 245));
	//this->addChild(block_green, 1);

	//BlockObject *_temp;
	//_temp = new BlockObject(this, 1);
	//this->addChild(_temp, 2);

	/*for (int i = 0; i < n_columns; i++)
	{
		for (int j = 0; j < n_rows; j++)
		{
			if (map[i][j] != 0)
			{
				BlockObject *bn;
				bn = new BlockObject(this);
				this->addChild(bn, 2);
			}
		}
	}*/

//	CBlockObject *bn;
///	bn = new CBlockObject(this);
//	this->addChild(bn, 2);

	CBlockManager *Manager = new CBlockManager(this);
	this->addChild(Manager, 2);

	scheduleUpdate();

    
    return true;
}

void CSInGame::update(float delta)
{

}

void CSInGame::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
