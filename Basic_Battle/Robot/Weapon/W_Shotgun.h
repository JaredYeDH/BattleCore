#pragma once

class W_Shotgun :
	public Weapon
{
protected:
	static int burst;		//һ����������ӵ�(���ű�)(����)
	static double gapRotation;	//�����ӵ�����Ƕ�

public:
	W_Shotgun(void);
	virtual ~W_Shotgun(void);
	
	//virtual weapontypename GetType(){return WT_Shotgun;}
	virtual bool Fire(int mnplt);
};

