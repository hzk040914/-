#include <iostream>
#include <Windows.h>
char c='0';
LONG  CALLBACK VectoredHandler(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	
	::MessageBox(NULL, "DLLע��ɹ�", "��ֻ��һ��û���õ���ʾ����", NULL);
	printf("�쳣��ַ��%08x\t", ExceptionInfo->ContextRecord->Eip);
	//�������쳣��Ҫ�����Լ�ѡ����ʽ���Լ��Ƿ��ȥ
	//�쳣����
	DWORD dwCode = ExceptionInfo->ExceptionRecord->ExceptionCode;
	//�жϽ��յ�����ʲô�쳣
	if (dwCode == EXCEPTION_BREAKPOINT) {
		//�쳣����
		printf("This is Int3\n");
		
		//���������봦���쳣�󣬻�ȥ������ִ�к���Ĵ���
		//EIP ָ��ָ��Ĵ�������������һ��Ҫִ�е�λ��
		//���ǽ�EIP+1���ͻ�ִ�к���Ĵ�����
		printf("��ѡ�����ִ��y��������ֹ����n��");
		scanf("%s", &c);
		if (c=='y')
		{
			ExceptionInfo->ContextRecord->Eip += 1;
			//���أ�����ִ��
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		else if (c=='n')
		{
			system("pause");
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else
		{
			printf("�������");
			return EXCEPTION_EXECUTE_HANDLER;
		}
		
	}
	return EXCEPTION_CONTINUE_EXECUTION;
}
int main()
{
	AddVectoredExceptionHandler(0, (PVECTORED_EXCEPTION_HANDLER)VectoredHandler);
	
	int i = 0;
	while (true)
	{
		i++;
		Sleep(500);
		if (i==3)
		{
			_asm {
				int 3
			}
			std::cout << "�쳣֮�����ִ�еĴ���" << std::endl;
		}
		printf("%d\n", i);
	}
/*	__asm int 3;*/
	system("pause");
	return 0;
}