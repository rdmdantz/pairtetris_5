#include "BlockObject.h"

CBlockObject::CBlockObject(cocos2d::Layer *_layer, int _x, int _y)
{
	m_pOrigin.setPoint(256.f + 15.f, 600.f - 15.f);
	m_iGridSize = 29;
	m_iType = 0;

	m_iPosX = _x;
	m_iPosY = _y;
	pSprite = CCSprite::create("block.png");
	//RenderBlock(0,0,1);
	pSprite->setVisible(false);
	pSprite->setPosition(m_pOrigin.x + (_x * m_iGridSize), m_pOrigin.y - (_y * m_iGridSize));
	this->addChild(pSprite);

	//scheduleUpdate();
	schedule(schedule_selector(CBlockObject::update), 0.1f);

}
CBlockObject::CBlockObject()
{
	m_pOrigin.setPoint(256.f + 15.f, 600.f - 15.f);
	m_iGridSize = 29;
	temp_x = 0;
	temp_y = 0;
	temp_c = 1;

	//scheduleUpdate();
	schedule(schedule_selector(CBlockObject::update), 0.1f);

}
CBlockObject::~CBlockObject()
{

}

void CBlockObject::update(float delta)
{
	
	RenderBlock(m_iPosX, m_iPosY, m_iType);
}

void CBlockObject::col(int _col)
{
	m_iType = _col;
}

void CBlockObject::RenderBlock(int _x, int _y, int type)
{
	m_iType = type;
	switch (m_iType)
	{
	default:
	{
			   pSprite->setVisible(false);
			   return;
	}
	case  1:
	{
			   pSprite->setVisible(true);
			   pSprite->setColor(ccColor3B::RED);
			   break;
	}
	case  2:
	{
			   pSprite->setVisible(true);
			   pSprite->setColor(ccColor3B::BLUE);
			   break;
	}
	case  3:
	{
			   pSprite->setVisible(true);
			   pSprite->setColor(ccColor3B::GREEN);
			   break;
	}
	case  4:
	{
			   pSprite->setVisible(true);
			   pSprite->setColor(ccColor3B::YELLOW);
			   break;
	}
	case  5:
	{
			   pSprite->setVisible(true);
			   pSprite->setColor(ccColor3B::ORANGE);
			   break;
	}
	case  6:
	{
			   pSprite->setVisible(true);
			   pSprite->setColor(ccColor3B::MAGENTA);
			   break;
	}
	case  7:
	{
			   pSprite->setVisible(true);
			   pSprite->setColor(ccColor3B(128, 60, 39));
			   break;
	}

	case  -1:
	{
				pSprite->setVisible(true);
				pSprite->setColor(ccColor3B::GRAY);
				break;
	}

	

	}

	
	
}