#pragma once
#include <WinSock2.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")
#define SPORT 8888 //�������˿ں�

//������
enum MSGTAG
{
	MSG_FILENAME = 1,	//�ļ���
	MSG_FILESIZE = 2,	//�ļ���С
	MSG_READY_READ = 3,	//׼������
	MSG_SENDFILE = 4,		//����
	MSG_SUCCESSED = 5,	//�������

	MSG_OPENFILE_FALID = 6//���߿ͻ����Ҳ����ļ�
};
#pragma pack(1)			//���ýṹ��1�ֽڶ���
#define PACKET_SIZE (1024-sizeof(int)*3)
struct MsgHeader		//��װ��Ϣͷ
{
	enum MSGTAG msgID;	//��ǰ��Ϣ��� 4
	union 
	{
		struct 
		{
			int fileSize;		//�ļ���С 4
			char fileName[256]; //�ļ���   256
		}fileInfo;
		struct 
		{
			int nStart;	//���ı��
			int nsize;//�ð������ݴ�С
			char buf[PACKET_SIZE];
		}packet;
	};
};
#pragma pack()


//��ʼ��socket��
bool initSocket();

//�ر�socket��
bool closeSocket();

//�����ͻ�������
void listenToClient();

//������Ϣ
bool processMsg(SOCKET clifd);

//��ȡ�ļ�������ļ���С
bool readFile(SOCKET, struct MsgHeader*);

//�����ļ�
bool sendfile(SOCKET clifd, MsgHeader* pmsg);