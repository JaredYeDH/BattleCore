#pragma once


//���λ�������(Robotman���������ò���)
class E_Robotman :
	public Engine
{
public:
	E_Robotman(void);
	virtual ~E_Robotman(void);


	virtual enginetypename GetType(){return ET_Robotman;}
	virtual bool Run(int);
	virtual bool Turn(int);
};

