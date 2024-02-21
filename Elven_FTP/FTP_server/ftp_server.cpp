#include <stdio.h>
#include "ftp_server.h"
char g_recvBuf[1024];//ȫ�ֱ����Զ���ʼ��Ϊ0,�������ܿͻ��˷��͵���Ϣ
int g_fileSize;		//�ļ���С
char* g_fileBuf; //�洢�ļ�����

int main()
{
	initSocket();

	listenToClient();

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
void listenToClient()
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
	serAddr.sin_addr.S_un.S_addr = ADDR_ANY;//����������������
	if (0 != bind(serfd, (struct sockaddr*)&serAddr, sizeof(serAddr)))
	{
		printf("bind faild��%d\n", WSAGetLastError());
		return;
	}

	//�����ͻ�������
	if (0 != listen(serfd,10))
	{
		printf("listen faild��%d\n", WSAGetLastError());
		return;
	}

	//�пͻ������ӣ��Ǿ�Ҫ��������
	struct sockaddr_in cliAddr;
	int len = sizeof(cliAddr);
	SOCKET clifd =  accept(serfd, (struct sockaddr*) & cliAddr, &len);
	if (INVALID_SOCKET == clifd)
	{
		printf("accept faild��%d\n", WSAGetLastError());
		return;
	}

	//��ʼ������Ϣ
	while (processMsg(clifd))
	{
		Sleep(5000);
	}
}

//������Ϣ
bool processMsg(SOCKET clifd)
{
	//�ɹ�������Ϣ�����ؽ��յ����ֽ��������ܹرշ���0������SOCKET_ERROR
	int nRes = recv(clifd, g_recvBuf, 1024, 0);
	if (nRes <= 0)
	{
		printf("�ͻ������ߡ�����%d\n", WSAGetLastError());
	}
	//��ȡ���յ�����Ϣ
	struct MsgHeader* msg = (struct MsgHeader*)g_recvBuf;
	switch (msg->msgID)
	{
	case MSG_FILENAME:
		printf("%s %d\n", msg->fileInfo.fileName, nRes);
		readFile(clifd, msg);
		break;
	case MSG_SENDFILE:
		printf("MSG_SENDFILE\n");
		sendfile(clifd, msg);
		break;
	default:
		break;
	}
	
	return true;
}

bool readFile(SOCKET clifd, MsgHeader* pmsg)
{
	FILE* pread = fopen(pmsg->fileInfo.fileName, "rb");
	if (pread == NULL)
	{
		printf("�Ҳ�����%s���ļ�", pmsg->fileInfo.fileName);
		struct MsgHeader msg = { msg.msgID = MSG_OPENFILE_FALID };
		if (SOCKET_ERROR == send(clifd, (char*)&msg, sizeof(struct MsgHeader),0))
		{
			printf("send faild��%d\n", WSAGetLastError());
		}
		return false;
	}
	//��ȡ�ļ��Ĵ�С
	fseek(pread,0,SEEK_END);
	g_fileSize = ftell(pread);
	fseek(pread, 0, SEEK_SET);
	//���ļ���С�����ͻ���
	//D:\asus\����\PROJECT\����\����\170.jpg
	struct MsgHeader msg ={msg.msgID = MSG_FILESIZE,msg.fileInfo.fileSize=g_fileSize};
	char tfnfame[200] = { 0 }, text[100];
	_splitpath(pmsg->fileInfo.fileName, NULL, NULL, tfnfame, text);
	strcat(tfnfame, text);
	strcpy(msg.fileInfo.fileName, tfnfame);
	send(clifd, (char*)&msg, sizeof(struct MsgHeader), 0);
	
	//���ļ�����
	g_fileBuf = (char*)calloc(g_fileSize + 1, sizeof(char));
	if (g_fileBuf == NULL)
	{
		printf("���ڴ�ռ�����ʧ�ܣ�\n");
		return false;
	}
	fread(g_fileBuf, sizeof(char), g_fileSize,pread);
	g_fileBuf[g_fileSize] = '\0';
	fclose(pread);

	return true;
}

	//�����ļ�
bool sendfile(SOCKET clifd, MsgHeader* pmsg)
{
	//����ļ��ĳ��ȴ���ÿ�����ݰ��ܴ��͵Ĵ�С��PACKET_SIZE����ô�ͷֿ鴫��
	for (size_t i = 0; i < g_fileSize; i+= PACKET_SIZE)
	{
		struct MsgHeader msg = { msg.msgID = MSG_READY_READ };//���߿ͻ���׼�������ļ�
		msg.packet.nStart = i;
		//���Ĵ�С�����ļ������ݵĴ�С
		if (i+PACKET_SIZE+1 > g_fileSize)
		{
			msg.packet.nStart = g_fileSize - i;
		}
		else
		{
			msg.packet.nStart = PACKET_SIZE;
		}
		memcpy(msg.packet.buf, g_fileBuf+ msg.packet.nStart, msg.packet.nsize);

		if (SOCKET_ERROR == send(clifd, (char*)&msg, sizeof(struct MsgHeader), 0))
		{
			printf("�ļ�����ʧ�ܣ�%d\n", WSAGetLastError());
		}
	}


	return true;
}