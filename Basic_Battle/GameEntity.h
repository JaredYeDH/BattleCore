#pragma once

//��Ӧ��MovieClip+Moving Object

//�����
class GameEntity
	:public BaseEntity
{
protected:
	
	shapes shapeType;		//��״���ͣ��Դ����֣��������ò�̫�ã�
						//��ø��ö��

	Circle circle;		//circle������Դ���point, x,y,r
	Box box;			//����
	Beam beam;			//����


	double rotation;	//�Ƕ�angle ��

	
	//�������ٶȣ���ת�ٶ�
	double vx;
	double vy;
	double vr;
	


public:
	GameEntity(void);
	virtual ~GameEntity(void);

	virtual void Update();		//onEnterFrame()

	Circle GetCircle()const{return circle;};
	Box GetBox()const{return box;};
	Beam GetBeam()const{return beam;}
	void GetVelocity(double&x,double&y,double&r)const{x=vx;y=vy;r=vr;};
	double GetRotation()const{return rotation;}

	double GetVX(){return vx;}
	double GetVY(){return vy;}
	double GetVR(){return vr;}

	shapes GetShape(){return shapeType;}


	void SetCircle(Circle c){circle=c;}

	void SetX(double xx){circle.x=xx;}
	void SetY(double yy){circle.y=yy;}
	void SetRotation(double rr){rotation=rr;}

	void SetVX(double vv){vx=vv;}
	void SetVY(double vv){vy=vv;}
	void SetVR(double vv){vr=vv;}

	void SetVelocity(double x,double y,double r){vx=x;vy=y;vr=r;}

	void SetShape(shapes s){shapeType=s;}

	void Init_GameEntity();		//��ʼ��



	bool HitTest(GameEntity &);	//��ײ���


	void SetEX(double ex){beam.ex=ex;}
	void SetEY(double ey){beam.ey=ey;}

	//�¼����
	virtual void HandleEvent(events msg,void* extraInfo)=0;
	
	static void MomentumHit(GameEntity &g1,GameEntity &g2);		//������ײ
	static void MomentumHit_Half(GameEntity &g1, GameEntity &g2);	//�붯����ײ��g2�̶���
};

