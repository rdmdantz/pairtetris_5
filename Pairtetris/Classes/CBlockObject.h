#ifndef __BLOCK_OBJECT_H__
#define __BLOCK_OBJECT_H__

#include "cocos2d.h"


USING_NS_CC;
class BlockObject : public cocos2d::Node
{
	public:
		BlockObject(cocos2d::Layer *_layer);
		~BlockObject();

		void RenderBlock(int x, int y, int type);
		CCSprite* pSprite;

		void update(float delta);

		int temp_x;
		int temp_y;
		int temp_c;

		//virtual CCRect	  Getbounding() = 0;
		//virtual Point	  GetPos() = 0;

		////set
		//virtual void SetPos(int _posx, int _posy) = 0;
		//virtual void SetPosY(int _posy) = 0;
		//virtual void SetSpeed(int _speed) = 0;
		//virtual void SetNum(int _type) = 0;
		//virtual void Damage(int _damage) = 0;
	
		////get
		//virtual int GetNum() = 0;
		//virtual int GetPosX() = 0;
		//virtual int GetPosY() = 0;
		//virtual int GetHP() = 0;
		//virtual int GetScore() = 0;
		//virtual int GetCoin() = 0;

		//virtual void AttachLayer(cocos2d::Layer *_layer){}
		//virtual void DeteachLayer(cocos2d::Layer* pLayer){}

	
	private:
		int m_iType;
		int m_iPosX;
		int m_iPosY;
		int m_iSpeed;
		int m_BlockSize;
		bool m_isLocked;
		float m_Origin_x;
		float m_Origin_y;

		//char _temp[32];

};

#endif //__BLOCK_OBJECT_H__