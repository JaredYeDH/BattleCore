//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "E_Spider.h"


E_Spider::E_Spider(void)
{
	shapeType=S_Circle;
	LoadData(ET_Spider);
	InitData();
	Init_GameEntity();
}


E_Spider::~E_Spider(void)
{
}


bool E_Spider::Run(int mnplt)
{
	//9-6 �Ķ�������
	//1,2,3,4 others  <===>  ��,��,��,��,ͣ

	//֩�����(Spider)ֻ�����������ƶ���

	switch(mnplt)
	{
	case 1:
		vx=-maxSpeed;
		vy=0;
		break;
	case 2:
		vx=maxSpeed;
		vy=0;
		break;
	case 3:
		vx=0;
		vy=-maxSpeed;
		break;
	case 4:
		vx=0;
		vy=maxSpeed;
		break;
	default:
		vx=0;
		vy=0;
		return false;
		//break;
	}
	return true;
}

bool E_Spider::Turn(int mnplt)
{
	//֩�����(Spider)����Ҫת��
	return false;
}