#include <iostream>
#include <Windows.h>

LONG MyVEHCallBack(
	struct _EXCEPTION_POINTERS* ExceptionInfo
) {
	::MessageBox(NULL, "DLL", "��ֻ��һ��û���õ���ʾ����", NULL);
	//�������쳣��Ҫ�����Լ�ѡ����ʽ���Լ��Ƿ��ȥ
	//�쳣����
	DWORD dwCode = ExceptionInfo->ExceptionRecord->ExceptionCode;
	//�жϽ��յ�����ʲô�쳣
	if (dwCode == EXCEPTION_BREAKPOINT) {
		//�쳣����
		std::cout << "This is Int3" << std::endl;
		printf("hello world\n");
		printf("%08x\n", ExceptionInfo->ContextRecord->Eip);
		::MessageBox(NULL, "DLLע��ɹ�", "��ֻ��һ��û���õ���ʾ����", NULL);
		system("pause");
		//���������봦���쳣�󣬻�ȥ������ִ�к���Ĵ���
		//EIP ָ��ָ��Ĵ�������������һ��Ҫִ�е�λ��
		//���ǽ�EIP+1���ͻ�ִ�к���Ĵ�����
		ExceptionInfo->ContextRecord->Eip += 1;
		//���أ�����ִ��
		return EXCEPTION_EXECUTE_HANDLER;
	}
	return EXCEPTION_CONTINUE_EXECUTION;
	return 0;
}

int main1()
{
	/*
	//�߳������Ļ�ȡ
	CONTEXT ctx;
	GetThreadContext(GetCurrentThread(), &ctx);
	//�����߳�������
	ctx.Dr0 = 111;
	SetThreadContext(GetCurrentThread(), &ctx);
	*/

	//ע�������쳣�������
	AddVectoredExceptionHandler(
		0,      //���ô�������˳�򣬳����һ�������쳣����������쳣
		(PVECTORED_EXCEPTION_HANDLER)MyVEHCallBack   //ָ��Ҫ���ô�������ָ�룬ʵ���Ͼ������Ƕ���Ĵ����쳣����
	);
	int i = 0;
	while (true)
	{
		i++;
		Sleep(500);
		if (i == 3)
		{
			_asm {
				int 3
			}
			std::cout << "�쳣֮��Ĵ���" << std::endl;
		}
		printf("%d\n", i);
	}
	//��������ʹ�û�࣬����һ��int3�ϵ�
	//int3 ����ϵ� 0xCC
	/*_asm int 3;*/
	

	

	system("pause");
	return 0;
}

// ��������������������������������
// ��Ȩ����������ΪCSDN������Shad0w - 2023����ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
// ԭ�����ӣ�https ://blog.csdn.net/qq_73985089/article/details/132384370
