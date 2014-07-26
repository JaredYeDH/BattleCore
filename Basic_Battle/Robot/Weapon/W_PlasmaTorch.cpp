//#include "stdafx.h"
#include "../../../stdafx.h"
#include "../Bullet/Bullet.h"
#include "W_PlasmaTorch.h"

W_PlasmaTorch::W_PlasmaTorch(void)
{
	LoadData(WT_PlasmaTorch);
	InitData();
	Init_GameEntity();
}


W_PlasmaTorch::~W_PlasmaTorch(void)
{
}



bool W_PlasmaTorch::Fire(int mnplt)
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
			new B_PlasmaBall(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetID()));
		
		pRobot->GetAchievementData().Add_Fire();
		return true;
	}
	return false;
}