#pragma once
#include "BaseEntity.h"
/*
AI���������Ϣ�Ĺ�����
����������ʽ������洢ÿһ֡����ĵ�����Ϣ
��һ֡����ʱ��������ڣ�����ջ���

��trace_global����ʹ��
*/

//����ģʽ
#define pTraceManager TraceManager::Instance()


class TraceManager
	:public BaseEntity
{
private:
	string text;


	TraceManager();
	virtual ~TraceManager();


public:
	static TraceManager* Instance();

	void AddText(string t);
	string OutputText();

	void Clear();

	virtual void HandleEvent(events msg,void* extraInfo);
};