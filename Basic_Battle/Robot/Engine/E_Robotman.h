#pragma once


//���λ�������(Robotman���������ò���)
class E_Robotman :
	public Engine
{
public:
	E_Robotman(enginetypename t = ET_Robotman);
	virtual ~E_Robotman(void);


	virtual enginetypename GetType(){return type;}
	virtual bool Run(int);
	virtual bool Turn(int);
};

