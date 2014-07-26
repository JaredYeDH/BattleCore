#pragma once
//#include "RobotAI_Interface.h"
#include "../Achievementstruct.h"

//#include"Weapon\Weapon.h"
//#include "Engine\Engine.h"

class Weapon;
class Engine;

class Robot
	:public BaseEntity		//�ƺ���û��Ҫ��ΪGameEntity������
{
protected:
	RobotAI_Interface* pRobotAI;		
	Weapon* pWeapon;
	Engine* pEngine;

	AchievementData_Battle achievement_data;

	//TODO:���������ͨ����������
	int AI_index;		//����AI��AIManager::pAI�е��±�

public:
	Robot(void);
	Robot(RobotAI_Interface*,int);
	//Robot(const Robot&);
	virtual ~Robot(void);

	virtual void Update(int);


	//void Damage(double dmg){pEngine->ModifyHp(-dmg);}

	//SetAI( ��������ƺ�Ӧ����dll�������ָ�� )

	void SetAI(RobotAI_Interface*);

	void SetWeapon(weapontypename);
	void SetEngine(enginetypename);


	RobotAI_Interface& GetAI(){return *pRobotAI;}
	Weapon& GetWeapon(){return *pWeapon;}
	Engine& GetEngine(){return *pEngine;}
	
	AchievementData_Battle& GetAchievementData(){return achievement_data;}
	int GetAIIndex(){return AI_index;}

	bool Survive();
	
	void SetX(double);
	void SetY(double);



	void Init();

	virtual void HandleEvent(events msg,void* extraInfo);
};

