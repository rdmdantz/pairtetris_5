#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class CSMenu : public cocos2d::Layer
{



public:

    static cocos2d::Scene* createScene();

	CSMenu();
	~CSMenu();
    virtual bool init();  
    
	Size visibleSize;
	Point origin;


	void menuStartCallback(Object* pSender);
	void menuQuitCallback(Object* pSender);
	

	CREATE_FUNC(CSMenu);
};

#endif // __NENU_SCENE_H__
