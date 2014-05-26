#include "AppDelegate.h"
#include "GameTitleScene.h"
#include "InGameScene.h"
USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
	auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Tetris (5)");
        director->setOpenGLView(glview);
		glview->setFrameSize(800, 600);
		glview->setDesignResolutionSize(800, 600, ResolutionPolicy::NO_BORDER);
    }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
	//auto scene = CSMenu::createScene();
	auto scene = CSInGame::createScene();
    director->runWithScene(scene);
	
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
