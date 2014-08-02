//include"../stdafx.h"
//#include "stdafx.h"
#include "../../stdafx.h"
#include "../GameEntity.h"
#include "Engine/Engine.h"
#include "Weapon/Weapon.h"
#include "RobotAIstruct.h"
#include "RobotAI_Interface.h"
#include "Robot.h"
#include "../Battlefield.h"


Robot::Robot(void):achievement_data()
{
	pWeapon=NULL;
	pEngine=NULL;
}

Robot::Robot(RobotAI_Interface* ai,int index):achievement_data()
{
	pRobotAI=ai;
	pWeapon=NULL;
	pEngine=NULL;

	AI_index=index;
}

/*
Robot::Robot(const Robot& r)
{
	//Robot��������ƹ��캯���ݲ���Ҫ

	//8-22 �ܱ�Ǹ��Ҫ
	//���·ת��ͻȻ����������ƹ��캯���Ƿ���Ҫ��
	//ֻҪ����ս�������У��Ͷ��ò���
	//����Ҫ���Ƶ�Ҳֻ��dll��pAI


	//����ĸ��ƹ��캯����������
	//???
	//������һ��ɵ�Ʒ�����switch(r.type)Ȼ��ֱ��ö�Ӧ��������Ĺ��캯��
	
	switch(r.pWeapon->GetType())
	{
	case WT_Cannon:
		pWeapon=new W_Cannon(*(W_Cannon*)r.pWeapon);
		break;


		//...
	}
	//pWeapon=new Weapon(*r.pWeapon);

	switch(r.pEngine->GetType())
	{
	case ET_Spider:
		pEngine=new E_Spider(*(E_Spider*)r.pEngine);

	case ET_Robotman:
		pEngine=new E_Robotman(*(E_Robotman*)r.pEngine);
		break;

	case ET_AFV:
		pEngine=new E_AFV();
		break;

	case ET_UFO:
		pEngine=new E_UFO();
		break;
		//...
	}
	

	//��������ָ�������switch��ɵ�ư취ʵ�֣�����pRobotAI�أ�
	//pRobotAI=new
}
*/

Robot::~Robot(void)
{
	//delete pRobotAI;
	pRobotAI=NULL;	//ָ����Ǽ��ص�AI����AIManager����ɾ
	delete pWeapon;
	delete pEngine;
}


bool Robot::Survive()
{
	if(pEngine!=NULL)
	{
		return pEngine->Survive();
	}
	return false;
}


void Robot::Update(int myID)
{
	//���ݵõ���a,b,c,d�Ȳ�����������������вٿ�
	//switch(a){ case x: pWeapon->Fire();...}
	//pEngine->Turn(b)...
	RobotAI_Order order;


	//AI˼������òٿز���order
	pRobotAI->Update(order,pBattlefield->GetInfo(),myID);

	//������Weapon�Ŀ���ٿ�
	if(pWeapon->Fire(order.fire))
	{
		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_Fire,&myID);
	}
	
	//������Engine���н�Run����תTurn�ٿأ��ı��ٶȣ�
	if(pEngine->Run(order.run))
	{
		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_Run,&myID);
	}
	if(pEngine->Turn(order.eturn))
	{
		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_EngineTurn,&myID);
	}

	//������Weapon����תTurn�ٿ�
	if(pWeapon->Turn(order.wturn))
	{
		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_WeaponTurn,&myID);
	}

	//Robot�н����ı�λ�õȣ�
	pEngine->Update();
	pWeapon->Update_Weapon(*pEngine);
	
}

void Robot::SetWeapon(weapontypename wtn)
{
	if(pWeapon!=NULL)
	{
		delete pWeapon;
	}

	switch(wtn)
	{
	case WT_Cannon:
		pWeapon=new W_Cannon();
		break;

	case WT_Machinegun:
		pWeapon=new W_Machinegun();
		break;

	case WT_Prism:
		pWeapon=new W_Prism();
		break;

	case WT_Tesla:
		pWeapon=new W_Tesla();
		break;

	case WT_RPG:
		pWeapon=new W_RPG();
		break;

	case WT_Shotgun:
		pWeapon=new W_Shotgun();
		break;


	case WT_PlasmaTorch:
		pWeapon=new W_PlasmaTorch();
		break;
		//...
	case WT_MissileLauncher:
		pWeapon=new W_MissileLauncher();
		break;

	case WT_ElectricSaw:
		pWeapon=new W_ElectricSaw();
		break;

	case WT_GrenadeThrower:
		pWeapon=new W_GrenadeThrower();
		break;

	default:
		//AI�͵�����������
		//Ĭ�ϵ�һ��
		cout<<"Weapon Select Error!\nGet Default Weapon...\n";
		pWeapon=new W_Cannon();
		break;
	}
	pWeapon->SetpRobot(this);
}


void Robot::SetEngine(enginetypename etn)
{
	if(pEngine!=NULL)
	{
		delete pEngine;
	}


	switch(etn)
	{
	case ET_Spider:
		pEngine=new E_Spider();
		break;

	case ET_Robotman:
		pEngine=new E_Robotman();
		break;

	case ET_AFV:
		pEngine=new E_AFV();
		break;

	case ET_UFO:
		pEngine=new E_UFO();
		break;

	default:
		//AI�͵�����������
		//Ĭ�ϵ�һ��
		cout<<"Engine Select Error!\nGet Default Engine...\n";
		pEngine=new E_Spider();
		break;
	}

	pEngine->SetpRobot(this);
}


void Robot::SetAI(RobotAI_Interface* ai)
{
	pRobotAI=ai;
	//AI_index=index;
}


void Robot::Init()
{
	pEngine->InitData();
	pWeapon->InitData();
}



void Robot::HandleEvent(events msg,void* extraInfo)
{

}

void Robot::SetX(double xx)
{
	pEngine->SetX(xx);
	pWeapon->SetX(xx);
}

void Robot::SetY(double yy)
{
	pEngine->SetY(yy);
	pWeapon->SetY(yy);
}