#include <stdio.h>
#include <windows.h>
int __cdecl ChecKey(int userkey)
{
	int result; // eax
	result = userkey * (userkey - 23) == -102;
	if (userkey * (userkey - 23) == -102)
	{
		result = userkey * userkey * userkey;
		if (result == 4913)
			return MessageBoxW(0, L"��ϲ�㿪ʼ��IDA������", L"ע��ɹ�", 0);
	}
	return result;
}
int main()
{
	__asm
	{
		jmp Label1
		_emit 0xe8
		Label1:
		//ע��Label����һ����ð�ţ���Ȼ�ᱨ���������ҵ���newline"
	}
	__asm
	{
		xor eax, eax
		test eax, eax
		je Label2
		_emit 0e8h
		Label2:
	}

	__asm
	{
		xor eax, eax
		test eax, eax
		je Label3
			jnz label0
			Label0:
				_emit 0e8h//e8��call����������ɶ����
		Label3:
	}
	printf("Test Junk Code");
	for (int userkey = 0; userkey < 0xFFFFFFFF; userkey++)
	{
		if (userkey * (userkey - 23) == -102)
		{
			if (userkey * userkey * userkey == 4913)
			{
				printf("�����ƽ⣺%d", userkey);
			}
		}
	}
	//�����������ʽ��һԪ���η���

	system("pause");
}