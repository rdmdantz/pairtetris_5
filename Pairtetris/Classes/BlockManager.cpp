#include "BlockManager.h"


CBlockManager::CBlockManager(cocos2d::Layer *_layer)
{
	layer = _layer;
	srand((unsigned int) time(NULL));

	 n_score=0;
	 n_lines=0;

	BagInit();
	//n_type = rand() % 7 + 1;;
	newBlock(GetFromBag());
	n_rot = 0;
	n_hold = 0;
	//n_type = 1;
	b_checkrot = false;
	b_BLeft = false;;
	b_BRight = false;
	b_holdcheck = true;
	f_fallrate = 0.09f;

	b_gameover = false;
	// Ű���� �̺�Ʈ ������
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(CBlockManager::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(CBlockManager::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// ��ġ&���콺 �̺�Ʈ ������
	auto listener_touch = EventListenerTouchOneByOne::create();
	listener_touch->setSwallowTouches(true);
	listener_touch->onTouchBegan = CC_CALLBACK_2(CBlockManager::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_touch, this);



	for (int i = 0; i < 4; i++)
	{
		oldposx[i]=0;
		oldposy[i]=0;
		newposx[i] = 0;
		newposy[i] = 0;
	}


	// ���� �ʱ�ȭ�ϰ� ���� ������
	for (int i = 0; i < n_columns; i++)
	{
		for (int j = 0; j < n_rows; j++)
		{
			
			map[i][j] = 0;

			if (j < 20)
			{
				Blocks[i][j] = new CBlockObject(_layer, i, j);
				layer->addChild(Blocks[i][j]);
			}

		}
	}

	// Ȧ�带 �ʱ�ȭ�ϰ� ���� ������
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Holds[i][j] = new CBlockObject(_layer, i+0.0f, j+0.0f);
			layer->addChild(Holds[i][j]);

			Nexts[i][j] = new CBlockObject(_layer, i + 0.0f, j + 0.0f,1);
			layer->addChild(Nexts[i][j]);
		}
	}


	scheduleUpdate(); // ������Ʈ
	// f_fallrate �� �ֱ�� FallUpdate�� ������Ʈ��
	schedule(schedule_selector(CBlockManager::FallUpdate), f_fallrate); 

}

CBlockManager::~CBlockManager()
{}


bool CBlockManager::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	CCPoint touchPoint = pTouch->getLocationInView();
	CCPoint touchGlPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	for (int i = 0; i < n_columns; i++)
	{
	for (int j = 0; j < n_rows - 3; j++)
	{
		if (Blocks[i][j]->GetRect().containsPoint(touchGlPoint))
		{
			Blocks[i][j]->Interaction();
		}
	}
	}

	return true;
}

void CBlockManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("Key with keycode %d pressed", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		if (!b_BLeft)
		{
			n_x--;
			DrawBlock(n_x, n_y, n_type, n_rot);
		}
	
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		if (!b_BRight)
		{
			n_x++;
			DrawBlock(n_x, n_y, n_type, n_rot);
		}
		
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		if (b_checkrot)
		{
			if (n_rot < 4)
				n_rot++;
			else
				n_rot = 0;
		}
		

	}
	if (keyCode == EventKeyboard::KeyCode::KEY_SHIFT)
	{
		if (b_holdcheck)
			HoldBlock(n_type);
	}
}

void CBlockManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("Key with keycode %d released", keyCode);
}


bool CBlockManager::CheckRotate()
{
	//�̸� ȸ���Ұ��� ��ġ�� �����Ѵ�.
	NextBlock(n_x, n_y, n_type, n_rot);

	//ȸ���� �������� �˻��Ѵ�
	for (int i = 0; i < 4; i++)
	{
		if ( ((map[newposx[i]][newposy[i]] != 0) && (map[newposx[i]][newposy[i]] != n_type)  )  || newposx[i] <0 || newposx[i] >9 || newposy[i] > 19)
			return false;
	}

	return true;
}

void CBlockManager::FallUpdate(float delta)
{


	for (int i = 0; i < 4; i++)
	{
		if (map[oldposx[i]][oldposy[i] + 1] != 0 && map[oldposx[i]][oldposy[i] + 1] != n_type)
		{
			for (int i = 0; i < 4; i++)
			{

				map[oldposx[i]][oldposy[i]] = -1;
				oldposx[i] = 0;
				oldposy[i] = 0;
				LineCheck();	// �������� üũ�Ѵ�.
			}
			log("%d", p_pointer);
			b_holdcheck = true;
			//n_type = rand() % 7 + 1;;
			newBlock(GetFromBag());
			break;
		}

	}

	
	if (n_y == 19 || oldposy[0] == 19 || oldposy[1] == 19 || oldposy[2] == 19 || oldposy[3] == 19)
	{
		for (int i = 0; i < 4; i++)
		{

			map[oldposx[i]][oldposy[i]] = -1;
			oldposx[i] = 0;
			oldposy[i] = 0;	// �������� üũ�Ѵ�.
			log("%d" , p_pointer);
			LineCheck();
		}
		b_holdcheck = true;	// Ȧ�尡 ������ ���·� ����
		//n_type = rand() % 7 + 1;;
		newBlock(GetFromBag()); // ���ο� ���� �����Ѵ�.
	}
	else if (n_y < 19)
	{

		n_y += 1;
	}
	b_checkrot = CheckRotate(); // ȸ������ ���� üũ

}
void CBlockManager::update(float delta)
{
	ShowNext();
	CheckPointer();
	for (int i = 0; i < n_columns; i++)
	{
		for (int j = 0; j < n_rows-3; j++)
		{
			Blocks[i][j]->SetType(map[i][j]);
		}
	}

	if (!b_gameover)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Holds[i][j]->SetType(hold[i][j]);
		}
	}
	else
	for (int i = 0; i < 4; i++)
	{

		for (int j = 0; j < 4; j++)
		{
			Holds[i][j]->SetType(rand()%7 + 1);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Nexts[i][j]->SetType(next[i][j]);
		}
	}

	DrawBlock(n_x, n_y, n_type, n_rot);
	for (int i = 0; i < 4; i++)
	{
		if (oldposx[i] == 0 ||  (map[oldposx[i] - 1][oldposy[i]] != 0 && !(map[oldposx[i] - 1][oldposy[i]] == n_type)) )
		{
			b_BLeft = true;
			break;
		}
		else
		{
			b_BLeft = false;
		}
		
	}
	
	for (int i = 0; i < 4; i++)
	{
		if (oldposx[i] == 9 || (map[oldposx[i] + 1][oldposy[i]] != 0 && !(map[oldposx[i] + 1][oldposy[i]] == n_type)))
		{
			b_BRight = true;
			break;
		}
		else
		{
			b_BRight = false;
		}

	}
	
}

void CBlockManager::newBlock(int _type)
{
	for (int i = 0; i < 4; i++)
	{

	//	Blocks[oldposx[i]][oldposy[i]]->col(-1);
		oldposx[i] = 0;
		oldposy[i] = 0;
	}

	//n_type = rand() % 7 + 1;;
	n_rot = 0;
	n_type = _type;
	n_x = 4;
	n_y = -1;
	DrawBlock(n_x, n_y, n_type, n_rot);
}

void CBlockManager::LineCheck()
{
	int count = 0;
	for (int j = n_rows-3 ; j > 0; j--)
	{
		
		count = 0;
		for (int i = 0; i < n_columns; i++)
		{
			
			count += map[i][j];
			if (count == -10) // �������� ���� ���� 
			{
				LineClear(j); // �ش� ������ �����
			}
		}
	}

	for (int k = 0; k < n_columns; k++)
	{
		if (map[k][0] == -1)
		{
			log("GAME OVER");
			GameOver();
		}
		
	}
}

void CBlockManager::GameOver()
{

	auto labelScore = LabelTTF::create("Game Over", "fonts/solo5.ttf", 50);
	//labelScore->setAnchorPoint(ccp(0.08f, 0.2f));
	labelScore->setPosition(ccp(210 + labelScore->getContentSize().width / 2 , 400 - labelScore->getContentSize().height / 2));
	this->addChild(labelScore, 2);

	int x , y = 19;
	b_gameover = true;
	while (true)
	{
		if (y <= -1)
		{
			break;
		}
		Blocks[0][y]->SetOver(true);
		Blocks[1][y]->SetOver(true);
		Blocks[2][y]->SetOver(true);
		Blocks[3][y]->SetOver(true);
		Blocks[4][y]->SetOver(true);
		Blocks[5][y]->SetOver(true);
		Blocks[6][y]->SetOver(true);
		Blocks[7][y]->SetOver(true);
		Blocks[8][y]->SetOver(true);
		Blocks[9][y]->SetOver(true);
		y--;
	}
}

void CBlockManager::LineClear(int _line)
{
	for (int i = 0; i < n_columns; i++)
	{ // �ش� ������ �������� ��� �����
		map[i][_line] = 0; 
	}

	for (int j = _line; j > 0;  j--)
	{
		for (int i = 0; i < n_columns; i++)
		{ // ������ ������ ä��� ���� ������ ������ ��ĭ�� ������.
			if (map[i][j] != 0)
			{
				map[i][j + 1] = -1;
				map[i][j] = 0;
			}
		}
	}

	n_lines++;
	n_score++;
}

void CBlockManager::HoldBlock(int _type)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4;j++)
			hold[i][j] = 0;

	if (n_hold == 0)
	{
		n_hold = _type;
		n_type = GetFromBag();
		
		for (int i = 0; i < 4; i++)
		{
			map[oldposx[i]][oldposy[i]] = 0;
		}
		newBlock(n_type);
		b_holdcheck = false;
	}
	else
	{
		n_type = n_hold;
		n_hold = _type;
		for (int i = 0; i < 4; i++)
		{
			map[oldposx[i]][oldposy[i]] = 0;
		}
		newBlock(n_type);
		b_holdcheck = false;
	}
	switch (n_hold)
	{
	case 0:
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				hold[i][j] = 0;
		break;
	case 1:
		hold[1][2] = 1;
		hold[1 + 1][2] = 1;
		hold[1 + 2][2] = 1;
		hold[1 - 1][2] = 1;
		break;
	case 2:
		hold[1][2] = 2;
		hold[1 - 1][2 + 1] = 2;
		hold[1 + 1][2] = 2;
		hold[1 - 1][2] = 2;
		break;
	case 3:
		hold[1][2] = 3;
		hold[1 + 1][2 + 1] = 3;
		hold[1 + 1][2] = 3;
		hold[1 - 1][2] = 3;
		break;
	case 4:
		hold[1][2] = 4;
		hold[1 + 1][2 + 1] = 4;
		hold[1][2 + 1] = 4;
		hold[1 + 1][2] = 4;
		break;
	case 5:
		hold[1][2] = 5;
		hold[1 + 1][2] = 5;
		hold[1][2 + 1] = 5;
		hold[1 - 1][2 + 1] = 5;
		break;
	case 6:
		hold[1][2] = 6;
		hold[1][2 + 1] = 6;
		hold[1 + 1][2] = 6;
		hold[1 - 1][2] = 6;
		break;
	case 7:
		hold[1][2] = 7;
		hold[1 - 1][2] = 7;
		hold[1][2 + 1] = 7;
		hold[1 + 1][2 + 1] = 7;
		break;
	}


}

void CBlockManager::NextBlock(int x, int y, int _Type, int _Rotate)
{
	int _rot = _Rotate;

	if (_rot < 4)
		_rot += 1;
	else
		_rot = 0;

	switch (_Type)
	{
	case 1: // �����
		switch (_rot)//rotate is 0,1,2,3 : 0 is basic
		{
		default:
		case 0:
		case 2:
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x + 1; newposy[1] = y;
			newposx[2] = x + 2; newposy[2] = y;
			newposx[3] = x - 1; newposy[3] = y;
			break;
		case 1://stand up - ing I
		case 3:
			newposx[0] = x; newposy[0] = y - 1;
			newposx[1] = x; newposy[1] = y;
			newposx[2] = x; newposy[2] = y + 1;
			newposx[3] = x; newposy[3] = y + 2;
			break;
		}
		break;
	case 2://����
		//��
		switch (_rot)
		{
		default:
		case 0:
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x - 1; newposy[1] = y + 1;
			newposx[2] = x + 1; newposy[2] = y;
			newposx[3] = x - 1; newposy[3] = y;
			break;
		case 1:
			//���
			//  ��
			//  ��
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x - 1; newposy[1] = y - 1;
			newposx[2] = x; newposy[2] = y - 1;
			newposx[3] = x; newposy[3] = y + 1;
			break;
		case 2:

			//     ��
			// ����
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x - 1; newposy[1] = y;
			newposx[2] = x + 1; newposy[2] = y;
			newposx[3] = x + 1; newposy[3] = y - 1;
			break;
		case 3:
			//   ��
			//   ��
			//   ���
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x; newposy[1] = y - 1;
			newposx[2] = x; newposy[2] = y + 1;
			newposx[3] = x + 1; newposy[3] = y + 1;
			break;
		}
		break;
	case 3://����
		//    ��
		switch (_rot)
		{
		default:
		case 0:
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x + 1; newposy[1] = y + 1;
			newposx[2] = x + 1; newposy[2] = y;
			newposx[3] = x - 1; newposy[3] = y;
			break;
		case 1:
			//  ��
			//  ��  
			//���
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x; newposy[1] = y + 1;
			newposx[2] = x; newposy[2] = y - 1;
			newposx[3] = x - 1; newposy[3] = y + 1;
			break;
		case 2:
			//  
			//��    
			//����
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x + 1; newposy[1] = y;
			newposx[2] = x - 1; newposy[2] = y;
			newposx[3] = x - 1; newposy[3] = y - 1;
			break;
		case 3:
			//���    
			//��
			//��
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x; newposy[1] = y + 1;
			newposx[2] = x; newposy[2] = y - 1;
			newposx[3] = x + 1; newposy[3] = y - 1;
			break;
		}
		break;
	case 4://���
		//���
		newposx[0] = x; newposy[0] = y;
		newposx[1] = x + 1; newposy[1] = y + 1;
		newposx[2] = x; newposy[2] = y + 1;
		newposx[3] = x + 1; newposy[3] = y;
		break;

	case 5://    ���
		//  ���
		switch (_rot)
		{
		default:
		case 0:
		case 2:
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x + 1; newposy[1] = y;
			newposx[2] = x; newposy[2] = y + 1;
			newposx[3] = x - 1; newposy[3] = y + 1;
			break;
		case 1:
		case 3:
			//  �� 
			//  ���
			//    ��
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x + 1; newposy[1] = y;
			newposx[2] = x; newposy[2] = y - 1;
			newposx[3] = x + 1; newposy[3] = y + 1;
			break;
		}
		break;
	case 6:
		//  ����
		//    ��
		switch (_rot)
		{
		default:
		case 0:
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x; newposy[1] = y + 1;
			newposx[2] = x + 1; newposy[2] = y;
			newposx[3] = x - 1; newposy[3] = y;
			break;
		case 1:
			//      ��
			//    ���
			//      ��
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x - 1; newposy[1] = y;
			newposx[2] = x; newposy[2] = y - 1;
			newposx[3] = x; newposy[3] = y + 1;
			break;
		case 2:
			//      ��
			//    ����
			//      
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x - 1; newposy[1] = y;
			newposx[2] = x + 1; newposy[2] = y;
			newposx[3] = x; newposy[3] = y - 1;
			break;
		case 3:
			//      ��
			//      ���
			//      ��
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x + 1; newposy[1] = y;
			newposx[2] = x; newposy[2] = y + 1;
			newposx[3] = x; newposy[3] = y - 1;
			break;

		}
		break;
	case 7://���
		//  ���
		switch (_rot)
		{
		default:
		case 0:
		case 2:
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x - 1; newposy[1] = y;
			newposx[2] = x; newposy[2] = y + 1;
			newposx[3] = x + 1; newposy[3] = y + 1;
			break;
		case 1:
		case 3:
			//    ��
			//  ���
			//  ��
			//
			newposx[0] = x; newposy[0] = y;
			newposx[1] = x - 1; newposy[1] = y;
			newposx[2] = x; newposy[2] = y - 1;
			newposx[3] = x - 1; newposy[3] = y + 1;
			break;
		}
		break;
	}
}
 
void CBlockManager::DrawBlock(int x, int y, int _Type, int _Rotate)
{
	map[oldposx[0]][oldposy[0]] = 0;
	map[oldposx[1]][oldposy[1]] = 0;
	map[oldposx[2]][oldposy[2]] = 0;
	map[oldposx[3]][oldposy[3]] = 0;

	switch (_Type)
	{
	case 1: // �����
		switch (_Rotate)//rotate is 0,1,2,3 : 0 is basic
		{
		default:
		case 0:
		case 2:
			map[x][y] = 1;
			map[x + 1][y] = 1;
			map[x + 2][y] = 1;
			map[x - 1][y] = 1;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x+1; oldposy[1] = y;
			oldposx[2] = x+2; oldposy[2] = y;
			oldposx[3] = x-1; oldposy[3] = y;
			break;
		case 1://stand up - ing I
		case 3:

			map[x][y-1] = 1;
			map[x][y] = 1;
			map[x][y+1] = 1;
			map[x][y+2] = 1;

			oldposx[0] = x; oldposy[0] = y-1;
			oldposx[1] = x; oldposy[1] = y;
			oldposx[2] = x; oldposy[2] = y+1;
			oldposx[3] = x; oldposy[3] = y+2;
			break;
		}
		break;
	case 2://����
		   //��
		switch (_Rotate)
		{
		default:
		case 0:
			map[x][y] = 2;
			map[x-1][y+1] = 2;
			map[x + 1][y] = 2;
			map[x - 1][y] = 2;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x-1; oldposy[1] = y+1;
			oldposx[2] = x+1; oldposy[2] = y;
			oldposx[3] = x-1; oldposy[3] = y;
			break;
		case 1:
			//���
			//  ��
			//  ��
			map[x][y] = 2;
			map[x - 1][y - 1] = 2;
			map[x][y-1] = 2;
			map[x][y+1] = 2;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x - 1; oldposy[1] = y - 1;
			oldposx[2] = x ; oldposy[2] = y-1;
			oldposx[3] = x ; oldposy[3] = y+1;
			break;
		case 2:
		
			//     ��
			// ����

			map[x][y] = 2;
			map[x - 1][y] = 2;
			map[x+1][y] = 2;
			map[x+1][y - 1] = 2;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x - 1; oldposy[1] = y;
			oldposx[2] = x+1; oldposy[2] = y ;
			oldposx[3] = x+1; oldposy[3] = y - 1;
			break;
		case 3:
			//   ��
			//   ��
			//   ���
			map[x][y] = 2;
			map[x][y-1] = 2;
			map[x][y+1] = 2;
			map[x + 1][y + 1] = 2;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x; oldposy[1] = y-1;
			oldposx[2] = x; oldposy[2] = y+1;
			oldposx[3] = x+1; oldposy[3] = y + 1;
			break;
		}
		break;
	case 3://����
		   //    ��
		switch (_Rotate)
		{
		default:
		case 0:
			map[x][y] = 3;
			map[x + 1][y + 1] = 3;
			map[x + 1][y] = 3;
			map[x - 1][y] = 3;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x+1; oldposy[1] = y + 1;
			oldposx[2] = x+1; oldposy[2] = y;
			oldposx[3] = x -1; oldposy[3] = y;
			break;
		case 1:
			//  ��
			//  ��  
			//���
			map[x][y] = 3;
			map[x][y + 1] = 3;
			map[x][y-1] = 3;
			map[x - 1][y+1] = 3;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x ; oldposy[1] = y + 1;
			oldposx[2] = x ; oldposy[2] = y-1;
			oldposx[3] = x - 1; oldposy[3] = y+1;
			break;
		case 2:
			//  
			//��    
			//����
			map[x][y] = 3;
			map[x+1][y] = 3;
			map[x-1][y] = 3;
			map[x - 1][y -1] = 3;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x+1; oldposy[1] = y ;
			oldposx[2] = x-1; oldposy[2] = y ;
			oldposx[3] = x - 1; oldposy[3] = y - 1;
			break;
		case 3:
			//���    
			//��
			//��
			map[x][y] = 3;
			map[x][y+1] = 3;
			map[x][y-1] = 3;
			map[x+1][y - 1] = 3;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x ; oldposy[1] = y+1;
			oldposx[2] = x; oldposy[2] = y-1;
			oldposx[3] = x + 1; oldposy[3] = y - 1;
			break;
		}
		break;
	case 4://���
		   //���


			map[x][y] = 4;
			map[x +1][y + 1] = 4;
			map[x][y+1] = 4;
			map[x +1][y] = 4;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x + 1; oldposy[1] = y+1;
			oldposx[2] = x ; oldposy[2] = y+1;
			oldposx[3] = x + 1; oldposy[3] = y;
			break;

	case 5://    ���
		   //  ���
		switch (_Rotate)
		{
		default:
		case 0:
		case 2:
			map[x][y] = 5;
			map[x+1][y] = 5;
			map[x][y+1] = 5;
			map[x - 1][y+1] = 5;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x + 1; oldposy[1] = y;
			oldposx[2] = x ; oldposy[2] = y+1;
			oldposx[3] = x - 1; oldposy[3] = y + 1;
			break;
		case 1:
		case 3:
			//  �� 
			//  ���
			//    ��
			map[x][y] = 5;
			map[x + 1][y] = 5;
			map[x][y - 1] = 5;
			map[x + 1][y + 1] = 5;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x + 1; oldposy[1] = y;
			oldposx[2] = x; oldposy[2] = y - 1;
			oldposx[3] = x + 1; oldposy[3] = y + 1;
			break;
		}
		break;
	case 6:
		   //  ����
		   //    ��
		switch (_Rotate)
		{
		default:
		case 0:
			map[x][y] = 6;
			map[x][y + 1] = 6;
			map[x + 1][y] = 6;
			map[x - 1][y] = 6;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x; oldposy[1] = y +1;
			oldposx[2] = x +1; oldposy[2] = y ;
			oldposx[3] = x - 1; oldposy[3] = y ;
			break;
		case 1:
			//      ��
			//    ���
			//      ��
			map[x][y] = 6;
			map[x - 1][y] = 6;
			map[x][y-1] = 6;
			map[x][y+1] = 6;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x - 1; oldposy[1] = y;
			oldposx[2] = x; oldposy[2] = y-1;
			oldposx[3] = x; oldposy[3] = y+1;
			break;
		case 2:
			//      ��
			//    ����
			//      
			map[x][y] = 6;
			map[x - 1][y] = 6;
			map[x+1][y] = 6;
			map[x][y -1] = 6;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x - 1; oldposy[1] = y;
			oldposx[2] = x+1; oldposy[2] = y ;
			oldposx[3] = x; oldposy[3] = y - 1;
			break;
		case 3:
			//      ��
			//      ���
			//      ��
			map[x][y] = 6;
			map[x + 1][y] = 6;
			map[x][y+1] = 6;
			map[x][y - 1] = 6;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x + 1; oldposy[1] = y;
			oldposx[2] = x; oldposy[2] = y+1;
			oldposx[3] = x; oldposy[3] = y - 1;
			break;

		}
		break;
	case 7://���
		   //  ���
		switch (_Rotate)
		{
		default:
		case 0:
		case 2:
			map[x][y] = 7;
			map[x - 1][y] = 7;
			map[x][y+1] = 7;
			map[x + 1][y+1] = 7;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x - 1; oldposy[1] = y;
			oldposx[2] = x; oldposy[2] = y + 1;
			oldposx[3] = x+1; oldposy[3] = y + 1;
			break;
		case 1:
		case 3:
			//    ��
			//  ���
			//  ��
			//
			map[x][y] = 7;
			map[x - 1][y] = 7;
			map[x][y - 1] = 7;
			map[x - 1][y + 1] = 7;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x - 1; oldposy[1] = y;
			oldposx[2] = x; oldposy[2] = y - 1;
			oldposx[3] = x - 1; oldposy[3] = y + 1;
			break;
		}
		break;
	}
}


void CBlockManager::BagInit()
{
	p_pointer = 0;
	for (int i = 0; i < 14; i++)
		nextBlocks[i] = 0;

	int temp[7] = { 0 };

	bool tmpb = true;
	int j = 0;
	int a = -1;
	for (int i = 0; i<7; i++)
	{
		tmpb = true;
		a = rand() % 7 + 1;
		for (int j = 0; j <= i; j++)
		{
			if (a == temp[j])
			{

				tmpb = false;
			}
		}

		if (tmpb)
		{
			nextBlocks[i] = a;
			temp[i] = a;
		}
		else
			i -= 1;
	}
}
int CBlockManager::GetFromBag()
{

	if (p_pointer < 13)
		return nextBlocks[p_pointer++];
	else
	{
		p_pointer = 0;
		return nextBlocks[13];
	}

}

void CBlockManager::CheckPointer()
{
	if (p_pointer == 2)
	{
		int temp[14] = { 0 };

		bool tmpb = true;
		int j = 0;
		int a = -1;
		for (int i = 7; i<14; i++)
		{
			tmpb = true;
			a = rand() % 7 + 1;
			for (int j = 7; j <= i; j++)
			{
				if (a == temp[j])
				{
					tmpb = false;
				}
			}

			if (tmpb)
			{
				nextBlocks[i] = a;
				temp[i] = a;
			}
			else
				i -= 1;
		}

	}
	else if (p_pointer == 9)
	{


		int temp[7] = { 0 };

		bool tmpb = true;
		int j = 0;
		int a = -1;
		for (int i = 0; i<7; i++)
		{
			tmpb = true;
			a = rand() % 7 + 1;
			for (int j = 0; j <= i; j++)
			{
				if (a == temp[j])
				{

					tmpb = false;
				}
			}

			if (tmpb)
			{
				nextBlocks[i] = a;
				temp[i] = a;
			}
			else
				i -= 1;
		}
	}
}

int CBlockManager::GetScore()
{
	return n_score;
}
int CBlockManager::GetLines()
{
	return n_lines;
}

void CBlockManager::ShowNext()
{
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		next[i][j] = 0;
	int n_switch=0;

	if (p_pointer < 13)
		n_switch = p_pointer;
	else
		n_switch = 0;
	switch (nextBlocks[n_switch])
	{

	case 1:
		next[1][2] = 1;
		next[1 + 1][2] = 1;
		next[1 + 2][2] = 1;
		next[1 - 1][2] = 1;
		break;
	case 2:
		next[1][2] = 2;
		next[1 - 1][2 + 1] = 2;
		next[1 + 1][2] = 2;
		next[1 - 1][2] = 2;
		break;
	case 3:
		next[1][2] = 3;
		next[1 + 1][2 + 1] = 3;
		next[1 + 1][2] = 3;
		next[1 - 1][2] = 3;
		break;
	case 4:
		next[1][2] = 4;
		next[1 + 1][2 + 1] = 4;
		next[1][2 + 1] = 4;
		next[1 + 1][2] = 4;
		break;
	case 5:
		next[1][2] = 5;
		next[1 + 1][2] = 5;
		next[1][2 + 1] = 5;
		next[1 - 1][2 + 1] = 5;
		break;
	case 6:
		next[1][2] = 6;
		next[1][2 + 1] = 6;
		next[1 + 1][2] = 6;
		next[1 - 1][2] = 6;
		break;
	case 7:
		next[1][2] = 7;
		next[1 - 1][2] = 7;
		next[1][2 + 1] = 7;
		next[1 + 1][2 + 1] = 7;
		break;
	}
}