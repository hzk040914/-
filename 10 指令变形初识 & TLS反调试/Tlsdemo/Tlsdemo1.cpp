#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include "LPC/ntdll.h"

//_IMAGE_TLS_DIRECTORY32
//��Ҫ�õ�TLS���������
#pragma comment(linker,"/INCLUDE:__tls_used")

DWORD isDebug = 0;
void NTAPI TLS_CALLBACK(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
	//::MessageBox(NULL, "TLS����ִ��1", "Elven", NULL);
	if (Reason == DLL_PROCESS_ATTACH)
	{
		::MessageBox(NULL, "TLS����ִ��1", "Elven", NULL);
		//�������ں˵�����Ϣ ��һ�������ǽ��̾�����ڶ������������ɶ(�����жϺ��ں�֮�������Ϣ����ϵ)
		//NtSetInformationThread(GetCurrentThread(), ThreadHideFromDebugger, 0, 0);

		//����ֵisDebugΪ0��û�����ԣ������Ϊ0֤����������
		NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort, (PVOID)&isDebug, sizeof(DWORD), NULL);
	}
}
void NTAPI TLS_CALLBACK2(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH)
	{
		::MessageBox(NULL, "TLS����ִ��2", "Elven", NULL);
		//�������ں˵�����Ϣ ��һ�������ǽ��̾�����ڶ������������ɶ(�����жϺ��ں�֮�������Ϣ����ϵ)
		//NtSetInformationThread(GetCurrentThread(), ThreadHideFromDebugger, 0, 0);

		//����ֵisDebugΪ0��û�����ԣ������Ϊ0֤����������
		NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort, (PVOID)&isDebug, sizeof(DWORD), NULL);
	}
}
int main(void)
{
// 	char array[] = { 0xD7,0xA2,0xB2,0xE1,0xB3,0xC9,0xB9,0xA6,0x00 };//ע��ɹ�
// 	for (int i = 0; i < 9; i++)
// 	{
// 		array[i] = array[i] ^ 0x10;
// 	}
	char array2[] = { 0xc7, 0xb2, 0xa2, 0xf1, 0xa3, 0xd9, 0xa9 ,0xb6 ,0x10};
	for (int i = 0; i < 9; i++)
	{
		array2[i] = array2[i] ^ 0x10^isDebug;//���������0��ô����κ�����Ϊԭ�������������������ʵ�ַ����ԣ���Ϊ������isDebug��䣬���Ҳ�ͻ��.
		//���ǻ�ü��OD�з������Բ�������Կ���û��Ҫע�⡣
	}
	//0xc7, 0xb2, 0xa2, 0xf1, 0xa3, 0xd9, 0xa9 ,0xb6 ,0x10
	MessageBox(NULL, array2, "Elven", MB_OK);
	system("pause");
	return 0;
}

//�½�һ�����ݣ��ŵ�TLS���Ŀ¼������
#pragma data_seg(".CRT$XLX")
PIMAGE_TLS_CALLBACK pTLS_CALLBACKs[] = { TLS_CALLBACK,TLS_CALLBACK2,NULL };
#pragma data_seg()