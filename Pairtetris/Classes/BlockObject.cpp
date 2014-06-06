#include "BlockObject.h"

CBlockObject::CBlockObject(cocos2d::Layer *_layer, int _x, int _y)
{
	// ��µ� ���� �������� �����Ѵ�.
	//m_pOrigin.setPoint(256.f + 15.f, 600.f - 15.f);
	m_pOrigin.setPoint(256.f + 15.f, 600.f - 15.f);
	// ���� �� ��ĭ�� ũ��
	m_iGridSize = 29;

	// ���� ���� ������ �����Ѵ�
	m_iType = 0;

	// ���� ��ġ
	m_iPosX = _x;
	m_iPosY = _y;

	m_isHoldnNext = false;
	m_isOver = false;

	pSprite = CCSprite::create("block.png");
	//RenderBlock(0,0,1);
	pSprite->setVisible(false);
	pSprite->setPosition(m_pOrigin.x + (_x * m_iGridSize), m_pOrigin.y - (_y * m_iGridSize));
	this->addChild(pSprite);

	m_rRect.setRect(
		pSprite->getPositionX() - 26/2,
		pSprite->getPositionY() - 26/2,
		26,
		26);

	//scheduleUpdate();
	schedule(schedule_selector(CBlockObject::update), 0.1f);

}

CBlockObject::CBlockObject(cocos2d::Layer *_layer, float _x, float _y)
{
	m_pOrigin.setPoint(72.f + 15.f, 552.f - 15.f);
	m_iGridSize = 29;
	m_iType = 0;

	m_iPosX = _x;
	m_iPosY = _y;

	m_isHoldnNext = true;
	m_isOver = false;

	pSprite = CCSprite::create("block.png");
	//RenderBlock(0,0,1);
	pSprite->setVisible(false);
	pSprite->setPosition(m_pOrigin.x + (_x * m_iGridSize), m_pOrigin.y - (_y * m_iGridSize));
	this->addChild(pSprite);

	m_rRect.setRect(
		pSprite->getPositionX() - 26 / 2,
		pSprite->getPositionY() - 26 / 2,
		26,
		26);

	//scheduleUpdate();
	schedule(schedule_selector(CBlockObject::update), 0.1f);

}

CBlockObject::CBlockObject(cocos2d::Layer *_layer, float _x, float _y,int i)
{
	m_pOrigin.setPoint(620.f + 15.f, 552.f - 15.f);
	m_iGridSize = 29;
	m_iType = 0;

	m_iPosX = _x;
	m_iPosY = _y;



	pSprite = CCSprite::create("block.png");
	//RenderBlock(0,0,1);
	pSprite->setVisible(false);
	pSprite->setPosition(m_pOrigin.x + (_x * m_iGridSize), m_pOrigin.y - (_y * m_iGridSize));
	this->addChild(pSprite);

	m_rRect.setRect(
		pSprite->getPositionX() - 26 / 2,
		pSprite->getPositionY() - 26 / 2,
		26,
		26);

	//scheduleUpdate();
	schedule(schedule_selector(CBlockObject::update), 0.1f);

}
CBlockObject::CBlockObject()
{
	m_pOrigin.setPoint(256.f + 15.f, 600.f - 15.f);
	m_iGridSize = 29;

	//scheduleUpdate();
	schedule(schedule_selector(CBlockObject::update), 0.1f);

}
CBlockObject::~CBlockObject()
{

}

void CBlockObject::update(float delta)
{
	/*if (m_isHoldnNext)
	{
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
		m_pOrigin.setPoint(620.f + 15.f, 552.f - 15.f);
	}*/

	if (!m_isHoldnNext)
	if (!m_isOver)
	RenderBlock(m_iPosX, m_iPosY, m_iType);
	else
	RenderBlock(m_iPosX, m_iPosY, rand()%7+1);

	if (m_isHoldnNext)
	RenderBlock(m_iPosX, m_iPosY, m_iType);
}

void CBlockObject::SetType(int _type)
{
	m_iType = _type;
}

void CBlockObject::SetOver(bool _over)
{
	m_isOver = _over;
}

void CBlockObject::Interaction()
{
	//if (pSprite->isVisible())
	if (m_iType == -1)
	pSprite->setRotation(pSprite->getRotationX()+45.f);
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