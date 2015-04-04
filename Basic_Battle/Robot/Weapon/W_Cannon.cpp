//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "Weapon.h"
#include "W_Cannon.h"

W_Cannon::W_Cannon(weapontypename t)
{
	LoadData(t);
	InitData();
	Init_GameEntity();
}


W_Cannon::~W_Cannon(void)
{
}



bool W_Cannon::Fire(int mnplt)
{
	//Ӧ�÷���һ���¼���Battlefield����������һ���ڵ�
	//�ͼ�һ��ľ����ô���һ��ָ��Battlefield��ָ���������������ܾ���Robot����Battlefield����������)
	if(General_Fire(mnplt))
	{
		double p=inaccuracy*(Random0_1()-0.5);//ƫ�ƽǶ�
		//double r=AnglePlus(AnglePlus(rotation,engineRotation),p);//�Ƕ�
		double r=AnglePlus(rotation,p);
		double a=AngleToRadian(r);//����


		bullettypename bt = (bullettypename)type;
		//bullettypename bt = BT_Cannonball;
		//if(type == WT_Apollo)
		//{
		//	bt = BT_ApolloBall;
		//}


		pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
			Add_Bullet,
			new B_Cannonball(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetBattlefieldID(),bt)  );
		
		pRobot->GetAchievementData().Add_Fire();

		return true;
	}
	return false;
}