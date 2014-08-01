#include "RobotAITest.h"


#ifdef ROBOT_AI_TEST



using namespace std;

RobotAITest::RobotAITest()
{

}


RobotAITest::~RobotAITest()
{

}


//-----------------------------------------------------
//1.������ɵ�ս������
//-----------------------------------------------------


void RobotAITest::Update(RobotAI_Order& order,const RobotAI_BattlefieldInformation& info,int myID)
{
	//֡���ݺ���
	//���ܣ���ÿһ֡�����ã������Ļ�������һ֡�Ķ�������
	//������order	...	���ײ���ָ����ں������и�����ֵ�Բ��ݻ�������һ֡����Ϊ
	//		info	...	ս����Ϣ
	//		myID	... �Լ�������info��robot�����Ӧ���±�
	//		(�⼸����������ϸ˵���ڿ����ֲ�����ҵ�����Ҳ������RobotAIstruct.h��ֱ���ҵ����ǵĴ���)
	
	order.fire=1+(1-myID);
	order.wturn=1;
	order.run=4;
	if(info.robotInformation[myID].engineTypeName!=ET_Robotman)
	{
		order.eturn=-1;
	}
	else
	{
		order.eturn=0;
	}
}



void RobotAITest::ChooseArmor(weapontypename& weapon,enginetypename& engine,bool a)
{
	//��ѡװ������
	//���ܣ���ս����ʼʱΪ��Ļ���ѡ����ʵ����������������ؾ�
	//������weapon	...	������ѡ����������ں������и�����ֵ
	//		engine	...	������ѡ������棬�ں������и�����ֵ
	//tip:	������Ĳ�����ö������ weapontypename �� enginetypename
	//		�����ĵ�������ϸ˵������Ҳ������RobotAIstruct.h��ֱ���ҵ����ǵĴ���
	//tip:	���һ��bool��û�õġ�������һ���˻�������

	//weapon=WT_Cannon;	//�����Ұ���ũ��
	//engine=ET_Spider;	//�����Ұ�С֩��

	weapon=(weapontypename)Random(0,8);
	engine=(enginetypename)Random(0,3);
}











//-----------------------------------------------------
//2.������Ϣ
//-----------------------------------------------------


string RobotAITest::GetName()
{
	//������Ļ��׵�����
	return "����Robo";
}

string RobotAITest::GetAuthor()
{
	//���ػ��������˻��Ŷӵ�����
	return "��ѧ��";
}




//����һ��(-255,255)֮��Ļ���������������ɫƫ��ֵ���졢�̡�����
//�������flash�ͻ��˵Ĳ���Ԥ����Ԥ����ɫ�����Ч��
int RobotAITest::GetWeaponRed()
{
	//����һ��-255-255֮�������,����������ɫ��ƫ��ֵ
	return -50;
}
int RobotAITest::GetWeaponGreen()
{
	//����һ��-255-255֮�������,����������ɫ��ƫ��ֵ
	return -50;
}
int RobotAITest::GetWeaponBlue()
{
	//����һ��-255-255֮�������,����������ɫ��ƫ��ֵ
	return -50;
}



//����һ��(-255,255)֮��Ļ��������ؾߵ���ɫƫ��ֵ���졢�̡�����
//�������flash�ͻ��˵Ĳ���Ԥ����Ԥ����ɫ�����Ч��
int RobotAITest::GetEngineRed()
{
	//����һ��-255-255֮�����,�����ؾߺ�ɫ��ƫ��ֵ
	return -50;
}
int RobotAITest::GetEngineGreen()
{
	//����һ��-255-255֮�������,�����ؾ���ɫ��ƫ��ֵ
	return -50;
}
int RobotAITest::GetEngineBlue()
{
	//����һ��-255-255֮�������,�����ؾ���ɫ��ƫ��ֵ
	return -50;
}









//-----------------------------------------------------
//3.�ò�������Ĵ�������
//-----------------------------------------------------


void RobotAITest::onBattleStart(const RobotAI_BattlefieldInformation& info,int myID)
{
	//һ��ս����ʼʱ�����ã����ܿ���������ʼ��
	//������info	...	ս����Ϣ
	//		myID	... �Լ�������info��robot�����Ӧ���±�

}

void RobotAITest::onBattleEnd(const RobotAI_BattlefieldInformation& info,int myID)
{
	//һ��ս������ʱ�����ã����ܿ������������㶯̬������ڴ�ռ䣨��������˵Ļ���
	//������info	...	ս����Ϣ
	//		myID	... �Լ�������info��robot�����Ӧ���±�
}


void RobotAITest::onHit(int launcherID,bullettypename btn)
{
	//���ӵ�����ʱ������
	//������btn	...	��������ӵ����ࣨö�����ͣ�
}



//TODO:�������ʵ�����Լ��ĺ���





#endif