#pragma once



#define pDispatcher EventDispatcher::Instance()
//����ģʽ
class EventDispatcher
{
private:
	EventDispatcher(void);
	~EventDispatcher(void);

public:
	static EventDispatcher* Instance();

	//������Ϣ��Ϊ��򵥣��Ȳ�����ʱ
	void DispatchEvent(int sender,int recevier,events msg,void* extraInfo);
};

