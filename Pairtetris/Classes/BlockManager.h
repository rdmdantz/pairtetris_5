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

		static const int n_columns = 10;//��
		static const int n_rows = 23;//��
		int map[n_columns][n_rows];
		CBlockObject* Blocks[n_columns][n_rows];


		float f_fallrate;//�����ֱ�

		int n_hold;
		int hold[4][4];
		CBlockObject* Holds[4][4];//Ȧ��ĭ�� ���� ���� �����ֱ� ���� ��

		void ShowNext();
		int next[4][4];
		CBlockObject* Nexts[4][4];//nextĭ�� ���� ���� �����ֱ� ���� ��

		int oldposx[4];
		int oldposy[4];//��� ���� ��ġ
		int newposx[4];
		int newposy[4];//���� ��ġ(ȸ����)

		bool b_checkrot;//ȸ���� �����Ѱ�
		int n_x;
		int n_y;
		int n_type;
		int n_rot;//���� �����ϴ� ���� ���� ����


		

		bool b_BLeft;
		bool b_BRight;//�̵��� �����ϴ°�

		bool b_holdcheck;//Ȧ�尡 �����Ѱ�


		void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
		void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
		bool onTouchBegan(Touch *pTouches, Event *pEvent);

		void DrawBlock(int x, int y, int _Type, int _Rotate);
		bool CheckRotate();
		void NextBlock(int x, int y, int _Type, int _Rotate);
		void update(float delta);
		void FallUpdate(float delta);


		void newBlock(int _type);//���� ����
		void LineCheck();//���� �˻�
		void LineClear(int _line);//���� �
		void GameOver();
		bool b_gameover;
		void HoldBlock(int _type);//Ȧ�� ���

		void BagInit();//7 ����(��¥)
		int GetFromBag();

		void CheckPointer();

		int nextBlocks[14];//���� ������ �迭
		int p_pointer;//���� ������ �迭�� ������. ��������. ��¥��.


		int n_score;
		int n_lines;

		int GetScore();
		int GetLines();
		/*
		ȸ��
		����
		�̵�
		���
		����

		7-bag
		hold
		Ŭ����

		now_block
		�� ������ ���� ȸ�� ������ �޸� �� ( ������ )
		*/
};


#endif // __BLOCK_MANAGER_H__
