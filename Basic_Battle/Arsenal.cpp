//#include "stdafx.h"
#include "../stdafx.h"
#include "Arsenal.h"
#include "GameEntity.h"
#include "Robot/Weapon/Weapon.h"
#include "Robot/Engine/Engine.h"
#include "DataLoader.h"
#include "struct.h"

Arsenal::Arsenal()
{
	LoadData();
	available=true;
}

Arsenal::~Arsenal()
{
}

void Arsenal::LoadData()
{
	respawning_time=0;

	respawning_time_max=pDataLoader->GetGameData()->respawningTime_Arsenal;
	circle.r=pDataLoader->GetGameData()->radium_Arsenal;
	shapeType=S_Circle;
}

void Arsenal::Touch(Robot& robot)
{
	
#ifdef ARSENAL_MODE_CHANGE_ARMOR
	//�����Ĺ����д�����
	
	weapontypename weapon;
	enginetypename engine;
	robot.GetAI().ChooseArmor(weapon,engine,true);

	Circle temp=robot.GetWeapon().GetCircle();
	double tvx,tvy,tvr,tr,tre;

	robot.GetWeapon().GetVelocity(tvx,tvy,tvr);
	tr=robot.GetWeapon().GetRotation();
	tre=robot.GetWeapon().GetEngineRotation();
	//TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//���������Ⱑ
	//?�������

	robot.SetWeapon(weapon);
	//robot.GetWeapon().ReLoad();
	robot.GetWeapon().SetCircle(temp);
	robot.GetWeapon().SetVelocity(tvx,tvy,tvr);
	robot.GetWeapon().SetRotation(tr);
	robot.GetWeapon().SetEngineRotation(tre);



	//����Engineʱ��hp����취
	//��ʱ��ͬ������?
	//robot.GetEngine().GetHp()/robot

	double ratio=robot.GetEngine().GetHpRatio();
	temp=robot.GetEngine().GetCircle();
	robot.GetEngine().GetVelocity(tvx,tvy,tvr);
	tr=robot.GetEngine().GetRotation();
	robot.SetEngine(engine);
	robot.GetEngine().SetHpByRatio(ratio);

	robot.GetEngine().SetCircle(temp);
	robot.GetEngine().SetVelocity(tvx,tvy,tvr);
	robot.GetEngine().SetRotation(tr);
	
#endif

	//2014_2_28,Ϊ�����ָ��Ժͼ򻯣���������ܲ��䵯ҩ�����ܸ����������ؾ�
	//��һ������Ҫ�޸ĵ��������ǶȲ����ؾ߶������Ƕ�����

#ifndef ARSENAL_MODE_CHANGE_ARMOR
	//��������ֻreload
	robot.GetWeapon().ReLoad();
#endif

	ResetRespawningTime();
}