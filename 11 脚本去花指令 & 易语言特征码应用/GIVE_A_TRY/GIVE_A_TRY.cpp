#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <random>
// ���ո�����ȫ������
int dword_4030B4[42] = {
	0x63B25AF1, 0xC5659BA5, 0x4C7A3C33, 0x0E4E4267, 0xB6117698, 0x3DE6438C, 0x84DBA61F, 0xA97497E6, 0x650F0FB3,
	0x84EB507C, 0xD38CD24C, 0xE7B912E0, 0x7976CD4F, 0x84100010, 0x7FD66745, 0x711D4DBF, 0x5402A7E5, 0xA3334351,
	0x1EE41BF8, 0x22822EBE, 0xDF5CEE48, 0xA8180D59, 0x1576DEDC, 0xFCD62B3B, 0x32AC1F6E, 0x9364A640, 0xC282DD35,
	0x14C5FC2E, 0xA765E438, 0x7FCF345A, 0x59032BAD, 0x9A5600BE, 0x5F472DC5, 0x5DDE0D84, 0x8DF94ED5, 0xBDF826A6,
	0x515A737A, 0x4248589E, 0x38A96C20, 0xCC7F6109, 0x2638C417, 0xD9BEB996
};
int loc_401166(int random, int i) {
	__asm{
		mov     eax, random
		mov     ecx,i
		mul     ecx
		mov     ecx, 0xFAC96621
		pop     eax
		push    edx
		mul     eax
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		mul     edx
		div     ecx
		mov     eax, edx
		pop     edx
		mul     edx
		div     ecx
// 		cmp     edx, [edi + ebx * 4]
// 		jnz     short loc_4011F2
		mov     eax,edx
	}
}
bool isBoomShakaLaka(int result, int i) 
{
	return result == dword_4030B4[i] ? true : false;
}
//���������
int bruteforceRand()
{
	int dword_46406C = 0x3133359;
	for (size_t i = 0; i < 0xFFFFFFFF; i++)
	{
		int boom = loc_401166(i, 'f');//��һ���ַ���f
		if (isBoomShakaLaka(boom, 0))
		{
			printf("BoomShakaLakal BoomShakaLaka! \n\rThe first fucking rand is: 0x%x \n\r",i);
			return i;
		}
	}
		
}

//�����������
int bruteforceSrand(int first)
{
	int dword_40406C = 0x31333359;//���˷��������ֵ������ȷ��
	for (size_t i = 0; i < 0xFFFFFFFF; i++)
	{
			//��Ϊ��α����������Ӷ����˾������һ���������
			int random = dword_40406C + i;
			srand(random);
			if (rand() == first)//�ƽ�����ĵ�һ�ε������
			{
				printf("captain! Your fucking seed is: 0x%0x\n\r", random);
				return random;
			}
	}		
}

int main(){
	// �����0x4077
	int rnd = bruteforceRand();
	//�����0x31333d38
	int seed = bruteforceSrand(rnd);
	int possibles = 0xFF * 42;//ȫ������
	srand(seed);
	printf("Givmme answer plz: ");
	//���ո����ı����ƽ�
	for (size_t i = 0; i < 42; i++)
	{
		int nextRnd = rand();//���е��ַ�����
		for (size_t j = 1; j < 0xFF; j++)
		{
		
			int fuck = loc_401166(nextRnd,j);
			if (isBoomShakaLaka(fuck,i))
			{
				printf("%c",j);
				break;
			}
		}
	}
	
	printf("\r\n");
	system("pause"); 
	return 0;
}