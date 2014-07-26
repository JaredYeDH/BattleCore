//#include "stdafx.h"
#include "../stdafx.h"


BattleMap::BattleMap():pObstacle(0,NULL),pArsenal(0,NULL)
{
}


void BattleMap::Construct_Map()
{
	//temp, static map

	//�����Ǳ߽�
	boundary.width=1366;
	boundary.height=680;
	boundary.x=boundary.width/2;
	boundary.y=boundary.height/2;

	
	B_Left=boundary.x-boundary.width/2;
	B_Right=boundary.x+boundary.width/2;
	B_Up=boundary.y-boundary.height/2;
	B_Down=boundary.y+boundary.height/2;
	

	//obstacle
	//temp�е�temp(�ظ����أ�delete������)
	num_obstacle=2;

	Obstacle* pO=new Obstacle();
	//
	pO->SetX(300);
	pO->SetY(250);
	pO->SetR(75);
	pO->SetShape(S_Circle);

	pObstacle.push_back(pO);

	pO=new Obstacle();
	pO->SetX(1066);
	pO->SetY(430);
	pO->SetR(75);
	pO->SetShape(S_Circle);

	pObstacle.push_back(pO);
	pO=NULL;

	//������
	birthPoint[0].x=B_Left+50;
	birthPoint[0].y=B_Up+50;
	birthPoint[1].x=B_Right-50;
	birthPoint[1].y=B_Down-50;


	//arsenal
	num_arsenal=2;
	Arsenal* pA;

	pA=new Arsenal();
	pA->SetX(50);
	pA->SetY(630);
	//pA->Set
	pArsenal.push_back(pA);

	pA=new Arsenal();
	pA->SetX(1316);
	pA->SetY(50);
	pArsenal.push_back(pA);

	pA=NULL;
}


BattleMap::~BattleMap()
{
	//����Battlefield::Sweep��
	//����Խ��Խ���ҡ���

	//stl��ԭʼָ��new������ɵ��
}