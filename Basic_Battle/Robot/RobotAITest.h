#pragma once


#define ROBOT_AI_TEST


#ifdef ROBOT_AI_TEST
#include<string>
#include<vector>

#include "../struct.h"
#include "RobotAIstruct.h"
#include "RobotAI_Interface.h"

class RobotAITest:public RobotAI_Interface
{
protected:
	//TODO:����������������Լ��ĳ�Ա����


public:

	//���Ի�����
	weapontypename m_weapon;
	enginetypename m_engine;



	//************************************************
	//��һ�κ����������Ҷ��������������ê�˱����

	RobotAITest();
	virtual ~RobotAITest();



	//-----------------------------------------------------
	//1.������ɵ�ս������
	//-----------------------------------------------------

	//֡���ݺ���
	//���ܣ���ÿһ֡�����ã������Ļ�������һ֡�Ķ�������
	//������order	...	���ײ���ָ����ں������и�����ֵ�Բ��ݻ�������һ֡����Ϊ
	//		info	...	ս����Ϣ
	//		myID	... �Լ�������info��robot�����Ӧ���±�
	//		(�⼸����������ϸ˵���ڿ����ֲ�����ҵ�����Ҳ������RobotAIstruct.h��ֱ���ҵ����ǵĴ���)
	virtual void Update(RobotAI_Order& order,const RobotAI_BattlefieldInformation& info,int myID);



	//��ѡװ������
	//���ܣ���ս����ʼʱΪ��Ļ���ѡ����ʵ����������������ؾ�
	//������weapon	...	������ѡ����������ں������и�����ֵ
	//		engine	...	������ѡ������棬�ں������и�����ֵ
	//tip:	������Ĳ�����ö������ weapontypename �� enginetypename
	//		�����ĵ�������ϸ˵������Ҳ������RobotAIstruct.h��ֱ���ҵ����ǵĴ���
	//tip:	���һ��bool��û�õġ�������һ���˻�������
	virtual void ChooseArmor(weapontypename& weapon,enginetypename& engine,bool);


	//-----------------------------------------------------






	//-----------------------------------------------------
	//2.������Ϣ
	//-----------------------------------------------------

	//������Ļ��׵�����
	virtual string GetName();
	
	//���ػ��������˻��Ŷӵ�����
	virtual string GetAuthor();



	//����һ��(-255,255)֮��Ļ���������������ɫƫ��ֵ���졢�̡�����
	//�������flash�ͻ��˵Ĳ���Ԥ����Ԥ����ɫ�����Ч��
	virtual int GetWeaponRed();
	virtual int GetWeaponGreen();
	virtual int GetWeaponBlue();

	//����һ��(-255,255)֮��Ļ��������ؾߵ���ɫƫ��ֵ���졢�̡�����
	//�������flash�ͻ��˵Ĳ���Ԥ����Ԥ����ɫ�����Ч��
	virtual int GetEngineRed();
	virtual int GetEngineGreen();
	virtual int GetEngineBlue();

	//-----------------------------------------------------




	//-----------------------------------------------------
	//3.�ò�������Ĵ�������
	//-----------------------------------------------------


	//һ��ս����ʼʱ�����ã����ܿ���������ʼ��
	//������info	...	ս����Ϣ
	//		myID	... �Լ�������info��robot�����Ӧ���±�
	virtual void onBattleStart(const RobotAI_BattlefieldInformation& info,int myID);
	
	
	
	//һ��ս������ʱ�����ã����ܿ������������㶯̬������ڴ�ռ䣨��������˵Ļ���
	//������info	...	ս����Ϣ
	//		myID	... �Լ�������info��robot�����Ӧ���±�
	virtual void onBattleEnd(const RobotAI_BattlefieldInformation& info,int myID);			
	
	
	//�л��׿���ʱ������
	//������fireID	... ����Ļ����±�
	virtual void onSomeoneFire(int fireID);


	//���ӵ�����ʱ������
	//������launcherID �������±�
	//		btn	...	��������ӵ����ࣨö�����ͣ�
	virtual void onHit(int launcherID,bullettypename btn);

	//-------------------------------------------------------------



	//***************************************************************



	//TODO:����������������Լ��ĺ�������,����RobotAI.cpp�б�д��Ӧ�ĺ�������







};


#endif