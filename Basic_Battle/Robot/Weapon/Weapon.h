#pragma once

//#include"../Engine/Engine.h"

class Engine;

//������
class Weapon :
	public GameEntity,public WeaponData
{
protected:
	//����ָ�꣨���static��
	Robot* pRobot;		//ָ�򸸼�ָ��

	//��̬���ݷŽ���WeaponData��

	static int coolingSpeed;	//��ȴ�ٶ�


	//��ǰ����
	int remainingAmmo;		//ʣ���ӵ���
	int cooling;		//��ǰ��ȴֵ��[0, coolingTime] ,Ϊ0����Fire()

	double engineRotation;	//���������rotation,��Robot�ฺ�����
							//����ʵ��ָ��AnglePlus(rotation,engineRotation)

	//?
	bool manipulation;		//�Ƿ���Բٿ�

public:
	Weapon(void);
	virtual ~Weapon(void);		//Ҫ��������

	void SetEngineRotation(double rr){engineRotation=rr;}
	void SetpRobot(Robot* r){pRobot=r;};

	virtual weapontypename GetType()=0;

	int GetRemainingAmmo(){return remainingAmmo;}
	int GetCooling(){return cooling;}
	int GetMaxAmmo(){return Ammo;}

	double GetEngineRotation(){return engineRotation;}

	bool General_Fire(int mnplt);
	void Heating(){cooling=coolingTime;}

	//�ӽű���������
	void LoadData(weapontypename);

	//�������ݳ�ʼ��
	void InitData();

	void ReLoad();

	//virtual void Update();
	void Update_Weapon(Engine &);
	void AjustPosition(Engine &);		//У׼xy����

	//�ٿط���
	virtual bool Fire(int mnplt)=0;		//���Ҫ�õ��¼����ƣ�(�о������¼�����֮���ֽ�����ˡ����������̺����ֵõ�Battlefield��ʵ�֣�)
	virtual bool Turn(int);

	virtual void HandleEvent(events msg,void* extraInfo){};

	
};

