//#include "stdafx.h"
#include "../stdafx.h"
#include "Trigger.h"

Trigger::Trigger()
{
	//����ʵ��ʵ����Щ
	//vx=0;
	//vy=0;
	//vr=0;
	//LoadData
}

Trigger::~Trigger()
{
}

void Trigger::Update_Trigger()
{
	if(respawning_time>0)
	{
		respawning_time--;
	}
}
