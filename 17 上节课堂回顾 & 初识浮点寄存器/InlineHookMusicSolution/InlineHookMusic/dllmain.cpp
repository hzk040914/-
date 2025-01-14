#include <Windows.h>
#include <stdio.h>
#define BEA_ENGINE_STATIC 
#define BEA_USE_STDCALL
#include "BeaEngine.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"BeaEngine.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")


//跳转返回到的地址
//int gJmpRetAddress;
//用来存放当前被HOOK的地址
int gHookAddress;
//长度
int gLen;
//HOOK代码写入后被覆盖掉的字节
byte gOldArray[256] = {0};

int CalcJmpAddress(int targetAddress, int hookAddress);
void PlayMusic();


//任意地址HOOK函数
void SupperHook(int hookAddress)
{
	gHookAddress = hookAddress;
	DISASM disam;
	disam.EIP = hookAddress;
	gLen = Disasm(&disam);
	while (gLen < 5)
	{
		disam.EIP += gLen;
		gLen += Disasm(&disam);
	}
	memcpy_s(gOldArray, gLen, (void*)hookAddress, gLen);
	//计算HOOK执行完毕后jmp返回的地址
	//gJmpRetAddress = hookAddress + gLen;
	//得到HOOK需要跳转到的函数地址
	int targetAddress = (int)&PlayMusic;
	//计算jmp xxxxxxxx这个指令中的xxxxxxxx的值
	//计算公式：目标地址-源地址-5
	int value = CalcJmpAddress(targetAddress, hookAddress);

	//修改内存页属性为可读可写可执行
	DWORD oldProtect;
	VirtualProtect((LPVOID)hookAddress, 0x1000, PAGE_EXECUTE_READWRITE, &oldProtect);
	//将要HOOK的地址第一个字节改成Jmp
	*((byte*)hookAddress) = 0xE9;
	//将跳转目标地址写入
	*((int*)(hookAddress + 1)) = value;
}

void __declspec(naked) PlayMusic()
{
	
	//把上一次的音乐关掉
	//mciSendString("close bkmusic", NULL, 0, NULL);
	//打开音乐
	mciSendString("open D:\\asus\\桌面\\PROJECT\\逆向\\逆向\\第17课\\InlineHookMusicSolution\\Debug\\播放的音乐.mp3 alias bkmusic", NULL, 0, NULL);
	//执行播放
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
		
	//打开浏览器
	//ShellExecute(NULL, "open", "https://www.52ying.top", NULL, NULL, SW_SHOWNORMAL);
	//恢复原始字节
	for (size_t i = 0; i < gLen; i++)
	{
		*((byte*)(gHookAddress + i)) = gOldArray[i];
	}
	_asm jmp gHookAddress
}

//计算jmp指令后的值
int CalcJmpAddress(int targetAddress, int hookAddress) 
{
	return targetAddress - hookAddress - 5;
}

//线程
DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter)
{
	int hookAddress;
	//创建控制台。
	AllocConsole();
	//将stdout设备输出的数据重定向到控制台输出
	freopen("CONOUT$", "w+t", stdout);
	//将stdin设备输入的数据重定向到控制台输入
	freopen("CONIN$", "r+t", stdin);
	while (true)
	{
		printf("请输入要HOOK的地址:");
		scanf("%08X", &hookAddress);
		//执行HOOK
		SupperHook(hookAddress);
		printf("HOOK执行完毕\n\n");
	}
	return 0;
}
BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
		case DLL_PROCESS_ATTACH:
		{
			HANDLE hTread = CreateThread(NULL, 0, ThreadProc, (LPVOID)NULL, 0, NULL);
		}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
		}
    return TRUE;
}

