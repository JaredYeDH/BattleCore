//#include "stdafx.h"
#include "../../../stdafx.h"
#include "../../GameEntity.h"
#include "Weapon.h"
#include "W_Tesla.h"


W_Tesla::W_Tesla(void)
{
	LoadData(WT_Tesla);
	InitData();
	Init_GameEntity();
}


W_Tesla::~W_Tesla(void)
{
}

bool W_Tesla::Fire(int mnplt)
{
	if(General_Fire(mnplt))
	{
		//ֱ����ȫ������ϵ�µ�
		double p=inaccuracy*(Random0_1()-0.5);//ƫ�ƽǶ�
		//double r=AnglePlus(AnglePlus(rotation,engineRotation),p);//�Ƕ�
		double r=AnglePlus(rotation,p);
		double a=AngleToRadian(r);//����

		pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
			Add_Bullet,
			new B_Tesla_Lightning(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetID()));

		pRobot->GetAchievementData().Add_Fire();
		return true;
	}
	return false;
}