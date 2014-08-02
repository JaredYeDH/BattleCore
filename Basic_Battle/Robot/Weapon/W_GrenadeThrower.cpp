#include "../../../stdafx.h"
#include "Weapon.h"
#include "W_GrenadeThrower.h"

W_GrenadeThrower::W_GrenadeThrower(void)
{
	LoadData(WT_GrenadeThrower);
	InitData();
	Init_GameEntity();
}


W_GrenadeThrower::~W_GrenadeThrower(void)
{
}



bool W_GrenadeThrower::Fire(int mnplt)
{
	//Ӧ�÷���һ���¼���Battlefield����������һ���ڵ�
	//�ͼ�һ��ľ����ô���һ��ָ��Battlefield��ָ���������������ܾ���Robot����Battlefield����������)
	if(General_Fire(mnplt))
	{
		double p=inaccuracy*(Random0_1()-0.5);//ƫ�ƽǶ�
		//double r=AnglePlus(AnglePlus(rotation,engineRotation),p);//�Ƕ�
		double r=AnglePlus(rotation,p);
		double a=AngleToRadian(r);//����

		pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
			Add_Bullet,
			new B_Grenade(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetBattlefieldID()));
		
		pRobot->GetAchievementData().Add_Fire();

		return true;
	}
	return false;
}