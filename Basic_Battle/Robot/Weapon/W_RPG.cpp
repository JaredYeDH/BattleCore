//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "W_RPG.h"


W_RPG::W_RPG(void)
{
	LoadData(WT_RPG);
	InitData();
	Init_GameEntity();
}


W_RPG::~W_RPG(void)
{
}

bool W_RPG::Fire(int mnplt)
{
	if(General_Fire(mnplt))
	{
		double p=inaccuracy*(Random0_1()-0.5);//ƫ�ƽǶ�
		//double r=AnglePlus(AnglePlus(rotation,engineRotation),p);//�Ƕ�
		double r=AnglePlus(rotation,p);
		double a=AngleToRadian(r);//����

		pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
			Add_Bullet,
			new B_RPGBall(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetID()));
		
		pRobot->GetAchievementData().Add_Fire();
		return true;
	}
	return false;
}