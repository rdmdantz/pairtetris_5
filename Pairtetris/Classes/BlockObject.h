#ifndef __BLOCK_OBJECT_H__
#define __BLOCK_OBJECT_H__

#include "cocos2d.h"


USING_NS_CC;
class CBlockObject : public cocos2d::Node
{
	public:
		CBlockObject(cocos2d::Layer *_layer, int _x, int _y);
		CBlockObject(cocos2d::Layer *_layer, float _x, float _y);
		CBlockObject(cocos2d::Layer *_layer, float _x, float _y, int i);
		CBlockObject();
		~CBlockObject();

		//SET
		void SetType(int _col);
		void SetOver(bool _over);

		//GET
		int		GetType() { return m_iType; }
		bool	GetLocked() { return m_isLocked; }
		CCPoint GetOrigin(){ return m_pOrigin; }
		Rect	GetRect() { return m_rRect; }

		//ACTION
		void Interaction();
		

		void RenderBlock(int x, int y, int type);
		CCSprite* pSprite;

		void update(float delta);

		int temp_x;
		int temp_y;
		int temp_c;

	
	private:
		int m_iType;
		int m_iPosX;
		int m_iPosY;
		int m_iSpeed;
		int m_iGridSize;
		bool m_isOver;
		bool m_isLocked;
		bool m_isHoldnNext;
		CCPoint m_pOrigin;

		Rect m_rRect;

};

#endif //__BLOCK_OBJECT_H__