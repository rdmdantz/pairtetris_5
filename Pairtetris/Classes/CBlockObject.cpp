#include "CBlockObject.h"

BlockObject::BlockObject(cocos2d::Layer *_layer)
{

	m_Origin_x = 256.f + 15.f;
	m_Origin_y = 600.f - 15.f;

	m_BlockSize = 29;
	temp_x = 0;
	temp_y = 0;
	temp_c = 1;

	pSprite = CCSprite::create("block.png");
	RenderBlock(0,0,1);
	this->addChild(pSprite);
	//scheduleUpdate();
	schedule(schedule_selector(BlockObject::update), 0.1f);

}

BlockObject::~BlockObject()
{

}

void BlockObject::update(float delta)
{
	/*for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			RenderBlock(j, i, rand()%8);
		}
	}*/
	
	/*if (temp_x < 9)
	{
		temp_x++;
	}
	else
	{
		temp_x = 0;
		temp_y++;
		if (temp_y > 19)
		{
			temp_y = 0;
		}
	}*/
	
	temp_x++;
	if (temp_x >= 10)
	{
		temp_x = 0;
		temp_y += 1;
		if (temp_y >= 20)
		{
			temp_y = 0;
		}
	}
	
	temp_c++;
	if (temp_c >= 7)
	{
		temp_c = 1;
	}
	RenderBlock(temp_x, temp_y, rand() % 7+1);
	
	//RenderBlock(temp_x, temp_y, temp_c);
}

void BlockObject::RenderBlock(int _x, int _y, int type)
{
	m_iType = type;
	switch (m_iType)
	{
	default:
	{
			   return;
	}
	case  1:
	{
			   pSprite->setColor(ccColor3B::RED);
			   break;
	}
	case  2:
	{
			   pSprite->setColor(ccColor3B::BLUE);
			   break;
	}
	case  3:
	{
			   pSprite->setColor(ccColor3B::GREEN);
			   break;
	}
	case  4:
	{
			   pSprite->setColor(ccColor3B::YELLOW);
			   break;
	}
	case  5:
	{
			   pSprite->setColor(ccColor3B::ORANGE);
			   break;
	}
	case  6:
	{
			   pSprite->setColor(ccColor3B::MAGENTA);
			   break;
	}
	case  7:
	{
			   pSprite->setColor(ccColor3B(128, 60, 39));
			   break;
	}

	case  -1:
	{
				pSprite->setColor(ccColor3B::GRAY);
				break;
	}

	

	}

	pSprite->setPosition(m_Origin_x + (_x * m_BlockSize), m_Origin_y - (_y * m_BlockSize));
	
}