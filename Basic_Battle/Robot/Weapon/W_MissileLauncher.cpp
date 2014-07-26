//#include "stdafx.h"
#include "../../../stdafx.h"
#include "Weapon.h"
#include "W_MissileLauncher.h"

W_MissileLauncher::W_MissileLauncher(void)
{
	LoadData(WT_MissileLauncher);
	InitData();
	Init_GameEntity();
}


W_MissileLauncher::~W_MissileLauncher(void)
{
}



bool W_MissileLauncher::Fire(int mnplt)
{
	//TODO:��������Fire�������׼ȷ��

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
			new B_TrackingMissile(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetID()));
		
		pRobot->GetAchievementData().Add_Fire();
		return true;
	}
	return false;
}