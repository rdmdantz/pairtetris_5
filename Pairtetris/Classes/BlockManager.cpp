#include "BlockManager.h"

CBlockManager::CBlockManager(cocos2d::Layer *_layer)
{

	layer = _layer;
	tempx = 0;
	tempfloat = 0.05f;
	temp2 = 1;
	temp3 = 0;
	array_ = Array::create();
	array_->retain();

	for (int i = 0; i < 4; i++)
	{
		oldposx[i]=0;
		oldposy[i]=0;
	}
	for (int i = 0; i < n_columns; i++)
	{
		for (int j = 0; j < n_rows; j++)
		{
			
			map[i][j] = 0;

			if (j < 20)
			{
				//CBlockObject *newblock = new CBlockObject(_layer, i, j);
				Blocks[i][j] = new CBlockObject(_layer, i, j);
				layer->addChild(Blocks[i][j]);
				array_->addObject(Blocks[i][j]);
			}

		}
	}

//	map[0][0] = 1;
//	map[1][2] = 2;
//	map[3][3] = -1;
//	DrawBlock(3, 4, 1, 0);

	schedule(schedule_selector(CBlockManager::update), 0.1f);
	schedule(schedule_selector(CBlockManager::FallUpdate), tempfloat);
	
}

CBlockManager::~CBlockManager()
{}
void CBlockManager::FallUpdate(float delta)
{
	DrawBlock(5, tempx, temp2, temp3);
	if (tempx < 19)
	{
		tempx += 1;
		
	}
	else
	{
		temp2++;
		tempx = 0;
		tempfloat -= 0.001f;
		schedule(schedule_selector(CBlockManager::FallUpdate), tempfloat);
		if (temp2 > 7)
		{
			temp3++;
			temp2 = 1;
			tempx = 0;
		}
	}
}
void CBlockManager::update(float delta)
{

	for (int i = 0; i < n_columns; i++)
	{
		for (int j = 0; j < n_rows-3; j++)
		{
			Blocks[i][j]->col(map[i][j]);		
		}
	}

	//CBlockObject *tem_obj = nullptr;
	//for (int i = array_->count(); i > 0; i--)
	//{
	//	//CCLOG("%d", i);
	//	tem_obj = (CBlockObject)array_->getLastObject();
	//	if (tem_obj != nullptr)
	//	{
	//	}
	//}

	//pObj = nullptr;
	//CCARRAY_FOREACH(array_, (CCObject)pObj)
	//{
	//	pObj->
	//	//CCSprite *spr = (CCSprite*) pObj;
	//	//spr->setc
	//	//pObj
	//	pObj = nullptr;
	//}



	//for (int i = 0; i >= array_->count(); i++)
	//{
	//	pSpr = (Sprite)array_->getObjectAtIndex(i);
	//}

	//ObstacleTypeObject *obstacle_spr = nullptr;
	//for (int i = array_bullet->count(); i > 0; i--)
	//{
	//	//CCLOG("%d", i);
	//	obstacle_spr = (ObstacleTypeObject*) array_obstacle->getLastObject();
	//	if (obstacle_spr != nullptr)
	//	if (obstacle_spr->getPositionY() + 50 < 0)
	//	{
	//		this->removeChild(obstacle_spr);
	//		array_obstacle->removeObject(obstacle_spr);
	//		obstacle_spr->release();
	//	}
	//}
}

void CBlockManager::DrawBlock(int x, int y, int _Type, int _Rotate)
{
	map[oldposx[0]][oldposy[0]] = 0;
	map[oldposx[1]][oldposy[1]] = 0;
	map[oldposx[2]][oldposy[2]] = 0;
	map[oldposx[3]][oldposy[3]] = 0;

	switch (_Type)
	{
	case 1: // бсбрбсбс
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
	case 2://бсбрбс
		   //бс
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
			//бсбс
			//  бр
			//  бс
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
		
			//     бс
			// бсбрбс

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
			//   бс
			//   бр
			//   бсбс
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
	case 3://бсбрбс
		   //    бс
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
			//  бс
			//  бр  
			//бсбс
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
			//бс    
			//бсбрбс
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
			//бсбс    
			//бр
			//бс
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
	case 4://брбс
		   //бсбс


			map[x][y] = 4;
			map[x +1][y + 1] = 4;
			map[x][y+1] = 4;
			map[x +1][y] = 4;

			oldposx[0] = x; oldposy[0] = y;
			oldposx[1] = x + 1; oldposy[1] = y+1;
			oldposx[2] = x ; oldposy[2] = y+1;
			oldposx[3] = x + 1; oldposy[3] = y;
			break;

	case 5://    брбс
		   //  бсбс
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
			//  бс 
			//  брбс
			//    бс
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
		   //  бсбрбс
		   //    бс
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
			//      бс
			//    бсбр
			//      бс
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
			//      бс
			//    бсбрбс
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
			//      бс
			//      брбс
			//      бс
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
	case 7://бсбр
		   //  бсбс
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
			//    бс
			//  бсбр
			//  бс
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
