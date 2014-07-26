#pragma once

class Engine :
	public GameEntity,public EngineData
{
protected:
	Robot* pRobot;


	

	//��ǰ����
	int hp;		//��ǰѪ��




	bool manipulation;		//�Ƿ���Բٿ�?

public:
	Engine(void);
	virtual ~Engine(void);

	virtual enginetypename GetType()=0;

	void SetpRobot(Robot* r){pRobot=r;}


	bool Survive()			//hp�Ƿ����0���Ƿ񻹻���
	{
		//Ҫ��Ҫ����һ�����˵��¼�
		return hp>0;
	}

	bool ModifyHp(int dhp)		//�޸�hpֵ�������Ƿ���
	{
		hp+=dhp;
		if(dhp<0)
		{
			pRobot->GetAchievementData().Add_damage(-dhp);
		}
		return Survive();
	}

	int GetHp(){return hp;}
	int GetMaxHp(){return maxHp;}

	double GetHpRatio(){return (double)hp/(double)maxHp;}
	void SetHpByRatio(double ratio){hp=(int)(maxHp*ratio);}


	//�ӽű���������
	void LoadData(enginetypename);
	//�������ݳ�ʼ��
	void InitData();

	//�ٿغ���
	virtual bool Run(int)=0;	//ֱ�����ٶȲٿ�
	virtual bool Turn(int)=0;	//������ת�ٿ�

	virtual void HandleEvent(events msg,void* extraInfo){};
};

