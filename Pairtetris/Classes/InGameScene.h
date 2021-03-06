#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BlockObject.h"
#include "SimpleAudioEngine.h"
#include "BlockManager.h"

class CSInGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	CocosDenshion::SimpleAudioEngine *m_BGM;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	LabelTTF* labelLine;
	LabelTTF* labelScore;

	CBlockManager *Manager;

	void update(float delta);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(CSInGame);
};

#endif // __HELLOWORLD_SCENE_H__
