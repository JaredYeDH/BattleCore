#pragma once


#define FRAME_NUM 10000

#define pRecordManager RecordManager::Instance()

class RecordManager :
	public BaseEntity
{
private:
	string fileType;	//�ļ���׺��
	string fileName;	//��ǰ¼������

	string fileRoute;	//·��
	string fileRoute_Final;	//����·��

	ofstream f;			//�ĵ�
	

	int hitID;			//��ǰ֡hitInfo���±�

	int currentFrame;

	Record_FrameInformation frameInfo[FRAME_NUM];


	RecordManager(void);
	virtual ~RecordManager(void);
public:
	static RecordManager* Instance();

	void Init();		//��ʼ��

	void Update_FrameInfo(RobotAI_BattlefieldInformation&);

	void NextFrame(){currentFrame+=1;}

	void SetFileName(string s){fileName=s;}

	void BuildFileRoute(){fileRoute_Final=fileRoute+fileName+fileType;}

	virtual void HandleEvent(events msg,void* extraInfo);

	void ReleaseRecord(int winner);	//����¼���ļ�

	void EnterFrame_Init();

	int GetCurFrame(){return currentFrame;}
};

