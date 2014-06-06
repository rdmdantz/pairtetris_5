#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "BlockObject.h"
#include "cocos2d.h"

USING_NS_CC;

typedef struct Node
{
	int data;
	struct Node *next;
}node;

class CBlockManager : public cocos2d::Node
{
	public:
		cocos2d::Layer *layer;

		CBlockManager(cocos2d::Layer *_layer);
		~CBlockManager();


		CBlockObject *pObj;
		CBlockObject baseobject;

		static const int n_columns = 10;//열
		static const int n_rows = 23;//행
		int map[n_columns][n_rows];
		CBlockObject* Blocks[n_columns][n_rows];


		float f_fallrate;//낙하주기

		int n_hold;
		int hold[4][4];
		CBlockObject* Holds[4][4];//홀드칸에 보일 블럭을 보여주기 위한 것

		void ShowNext();
		int next[4][4];
		CBlockObject* Nexts[4][4];//next칸에 보일 블럭을 보여주기 위한 것

		int oldposx[4];
		int oldposy[4];//사실 현재 위치
		int newposx[4];
		int newposy[4];//예측 위치(회전용)

		bool b_checkrot;//회전이 가능한가
		int n_x;
		int n_y;
		int n_type;
		int n_rot;//현재 낙하하는 블럭에 대한 정보


		

		bool b_BLeft;
		bool b_BRight;//이동을 제한하는것

		bool b_holdcheck;//홀드가 가능한가


		void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
		void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
		bool onTouchBegan(Touch *pTouches, Event *pEvent);

		void DrawBlock(int x, int y, int _Type, int _Rotate);
		bool CheckRotate();
		void NextBlock(int x, int y, int _Type, int _Rotate);
		void update(float delta);
		void FallUpdate(float delta);


		void newBlock(int _type);//새블럭 생성
		void LineCheck();//라인 검사
		void LineClear(int _line);//라인 껒여
		void GameOver();
		bool b_gameover;
		void HoldBlock(int _type);//홀드 기능

		void BagInit();//7 랜덤(가짜)
		int GetFromBag();

		void CheckPointer();

		int nextBlocks[14];//다음 블럭들의 배열
		int p_pointer;//다음 블럭들의 배열의 포인터. 포인터임. 진짜루.


		int n_score;
		int n_lines;

		int GetScore();
		int GetLines();
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
