#include <stdio.h>
#include "ftp_client.h"

char g_recvBuf[1024] = { 0 };
char* g_fileBuf; //�洢�ļ�����
int g_fileSize;  //�ļ��ܴ�С
char g_fileName[256];	//������������͹������ļ���
int main()
{
	initSocket();

	connectToHost();

	closeSocket();
	return 0;
}

//��ʼ��socket��
bool initSocket()
{
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		printf("WSAStartup faild��%d\n",WSAGetLastError());
		return false;
	}
	return true;
}
//�ر�socket��
bool closeSocket()
{
	
	if (0 != WSACleanup())
	{
		printf("WSACleanup faild��%d\n", WSAGetLastError());
		return false;
	}
	return true;
}
//�����ͻ�������
void connectToHost()
{
	//����server socket�׽��֣���ϵͳ�ں��з�����һ���ڴ�ռ䣩
	SOCKET serfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == serfd)
	{
		printf("soket faild:%d\n", WSAGetLastError());
		return;
	}
	//��socket��ip��ַ�Ͷ˿ں�
	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;//����ʹ���socketָ����һ��
	serAddr.sin_port = htons(SPORT);//�ѱ����ֽ���ת���������ֽ���
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//���ӷ�������ip��ַ

	//���ӵ�������
	
	if (0 != connect(serfd, (struct sockaddr*)&serAddr, sizeof(serAddr)))
	{
		printf("connect faild:%d\n", WSAGetLastError());
		return;
	}

	//��ʼ������Ϣ
	while (processMsg(serfd))
	{
		Sleep(5000);
	}
}

//������Ϣ
bool processMsg(SOCKET serfd)
{
	dowloadFileName(serfd);
	
	recv(serfd, g_recvBuf, 1024, 0);
	struct MsgHeader* msg = (struct MsgHeader*)g_recvBuf;
	switch (msg->msgID)
	{
	case MSG_OPENFILE_FALID:
		dowloadFileName(serfd);
		break;
	case MSG_FILESIZE:
		readyread(serfd, msg);
		break;
	case MSG_READY_READ:
		printf("MSG_READY_READ");
		writeFile(serfd, msg);
		break;
	default:
		break;
	}
	return true;
}
void dowloadFileName(SOCKET serfd)
{
	printf("hello!\n");
	char filename[1024] = "������ǿͻ��˵�Elven";
	printf("��������Ҫ���ص��ļ���");
	gets_s(filename, 1023);
	struct MsgHeader file ={ file.msgID = MSG_FILENAME};
	strcpy(file.fileInfo.fileName, filename);
	send(serfd, (char *) & file, sizeof(struct MsgHeader), 0);
	//printf("%d %s", file.msgID, file.fileInfo.fileName);
}

void readyread(SOCKET serfd,struct MsgHeader*pmsg)
{
	strcpy(g_fileName , pmsg->fileInfo.fileName);
	g_fileSize = pmsg->fileInfo.fileSize;
	g_fileBuf = (char*)calloc(g_fileSize + 1, sizeof(char));//������ڴ�ռ�
	if (g_fileBuf == NULL)
	{
		printf("���ڴ�ռ�����ʧ�ܣ�\n");
	}
	else
	{
		struct MsgHeader msg = { msg.msgID = MSG_SENDFILE };
		if (SOCKET_ERROR == send(serfd, (char*)&msg, sizeof(struct MsgHeader), 0))
		{
			printf("send faild:%d\n", WSAGetLastError());
			return;
		}
		
	}
	printf("size: %d	filename: %s", pmsg->fileInfo.fileSize, pmsg->fileInfo.fileName);
	//׼���ڴ棬pmsg->fileInfo.fileSize
	//׼�������������� MSG_READY_READ
}

bool writeFile(SOCKET serfd, struct MsgHeader* pmsg)
{
	int nStart = pmsg->packet.nStart;
	int nsize = pmsg->packet.nsize;
	memcpy(g_fileBuf,pmsg->packet.buf,pmsg->packet.nsize);
	printf("packet: %d %d\n", nStart + nsize, g_fileSize);
	if (nStart + nsize >= g_fileSize)
	{
		FILE* pwrite = fopen(g_fileName, "wb");
		if (pwrite == NULL)
		{
			printf("write file error������\n");
			return false;
		}
		fwrite(g_fileBuf, sizeof(char), g_fileSize, pwrite);
		fclose(pwrite);
		free(g_fileBuf);
		g_fileBuf = NULL;
		struct MsgHeader msg = { msg.msgID = MSG_SUCCESSED };
		send(serfd, (char*)&msg, sizeof(struct MsgHeader), 0);
	}

	return true;
}
