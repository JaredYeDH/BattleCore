#include "../../../stdafx.h"
#include "Weapon.h"
#include "W_MineLayer.h"

W_MineLayer::W_MineLayer(void)
{
	coolingTime_Tiny=pDataLoader->GetGameData()->coolingTime_Tiny_MineLayer;
	ammoConsumption_Miner=pDataLoader->GetGameData()->ammoConsumption_Mine_MineLayer;

	LoadData(WT_MineLayer);
	InitData();
	Init_GameEntity();


}


W_MineLayer::~W_MineLayer(void)
{
}



bool W_MineLayer::Fire(int mnplt)
{
	if(mnplt==1)
	{
		//����
		if(cooling<=0)
		{
			//��ȴ��ɣ����Կ���
			cooling=coolingTime;	//ǹ�ܷ���
			if(remainingAmmo>0)
			{
				//TODO:���׵ĺĵ������Դ���1
				remainingAmmo-=ammoConsumption_Miner;		//��ҩ����

				pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
					Add_Bullet,
					new B_Mine(circle.x,circle.y,0,pRobot->GetBattlefieldID()));

				pRobot->GetAchievementData().Add_Fire();

				return true;
			}
		}
	}
	else if(mnplt==2)
	{
		//�����ӵ�
		//TODO:�����ӵ�����ȴʱ�������Դ���0
		if(cooling<=coolingTime-coolingTime_Tiny)
		{
			//��ȴ��ɣ����Կ���
			cooling=coolingTime;	//ǹ�ܷ���
			if(remainingAmmo>0)
			{
				remainingAmmo-=1;			//��ҩ����

				double p=inaccuracy*(Random0_1()-0.5);//ƫ�ƽǶ�
				double r=AnglePlus(rotation,p);
				double a=AngleToRadian(r);//����

				pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
					Add_Bullet,
					new B_TinyBall(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetBattlefieldID()));

				pRobot->GetAchievementData().Add_Fire();


				return true;
			}
		}
	}

	return false;
}