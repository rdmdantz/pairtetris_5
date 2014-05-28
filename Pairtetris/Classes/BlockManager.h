#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "BlockObject.h"
#include "cocos2d.h"

USING_NS_CC;

class CBlockManager : public cocos2d::Node
{
	public:
		cocos2d::Layer *layer;


		CBlockManager(cocos2d::Layer *_layer);


		~CBlockManager();
		CBlockObject *pObj;
		Array *array_;
		CBlockObject baseobject;

		static const int n_columns = 10;
		static const int n_rows = 23;
		int map[n_columns][n_rows];
		CBlockObject* Blocks[n_columns][n_rows];
		float tempfloat;
		int tempx;
		int temp2;
		int temp3;
		int oldposx[4];
		int oldposy[4];
		void DrawBlock(int x, int y, int _Type, int _Rotate);

		void update(float delta);
		void FallUpdate(float delta);
		/*
		회전
		낙하
		이동
		모양
		제한

		7-bag
		hold
		클리어

		now_block
		블럭 종류에 따라서 회전 공식을 달리 함 ( 세종류 )
		*/
};


#endif // __BLOCK_MANAGER_H__
