//#include "stdafx.h"
#include "../stdafx.h"
#include "TraceManager.h"

TraceManager::TraceManager()
{
}

TraceManager::~TraceManager()
{
}


TraceManager* TraceManager::Instance()
{
	static TraceManager instance;
	return &instance;
}

void TraceManager::AddText(string t)
{
	if(t!="")
	{
		text=text+t+'\n';
	}
}

string TraceManager::OutputText()
{
	//TODO:�봰��Ľӿ�

	return text;
}

void TraceManager::Clear()
{
	text.clear();
}

void TraceManager::HandleEvent(events msg,void* extraInfo)
{
	
}