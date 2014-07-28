#pragma once
#include "GameEntity.h"
#include "Robot/RobotAIstruct.h"
#include "Robot/RobotAI_Interface.h"
#include "Robot/Robot.h"
//������


class Trigger:public GameEntity
{
protected:
	bool available;		//�ɱ��Ӵ�
	int respawning_time;	//��ȴʱ��
	int respawning_time_max;	//�����ȴʱ��


public:
	Trigger();
	virtual ~Trigger();

	void SetActive(bool b){available=b;}
	void ResetRespawningTime(){respawning_time=respawning_time_max;}

	int GetRespawningTime(){return respawning_time;}


	virtual void LoadData()=0;

	virtual void Touch(Robot&)=0;		//��������������

	virtual void Update_Trigger();		//����

	bool IsActive(){return available && respawning_time<=0;}
};