#include "InDialog.h"

HWND g_hEdit1;
HWND g_hEdit2;
HWND g_hDialog;
char g_szEMap[255];
DWORD g_VA;
DWORD g_dwVAddr;
byte *g_byVAddr;
DWORD g_SIZE;
DWORD g_RVASIZE;

typedef struct {
	char szName[40];
	int  nSize;
	int  nOffset;
	byte opcode[80];
}Node,*pNode;

typedef struct  
{
	int nDate;
	char *szGuid;
	char Unknow[28];
	char *szLibName;
	char Unknow1[60];
	int nComCount;
	long Unknow3;
	DWORD pFirstCom;
}*pElib;


/********************************************/
/*   ������Ϣ�������WndProc                */
/********************************************/
LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG)
	{
		g_hDialog = hwnd;
		g_hEdit1 = GetDlgItem(hwnd,IDC_EDIT1);
		g_hEdit2 = GetDlgItem(hwnd,IDC_EDIT2);
		SendMessageA(hwnd,WM_SETICON,WPARAM(0),LPARAM(g_hIcon));
		SendMessageA(hwnd,WM_SETICON,WPARAM(1),LPARAM(g_hIcon));
		return 1;
		
	}
	else if (uMsg == WM_COMMAND)
	{
		if (wParam == IDC_BUTTON1)
		{
			if (_Getcputhreadid())
			{
				CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(&EDebugStart),NULL,NULL,NULL);
			}
			else
			{
				_Flash("����δ�������!");
			}
		}
		return 1;
	}
	else if(uMsg == WM_CLOSE)
	{
		EndDialog(hwnd,0);
		return 1;
	}
	else
	{
		return 0;
	}

}



/**********************************************/
/*    ��������������                          */
/**********************************************/
DWORD Search_Bin(byte *pSrc,byte *pTrait,int nSrcLen, int nTraitLen)
{
	if (IsBadReadPtr(pSrc,4)==TRUE)
	{
		return 0;
	}
	int i,j,k;
	for (i=0;i<=(nSrcLen-nTraitLen);i++)
	{
		if (pSrc[i]==pTrait[0])
		{
			k=i;
			j=0;
			while (j<nTraitLen)
			{
				k++;j++;
				if (pTrait[j]==144)
				{
					continue;
				}
				if (pSrc[k]!=pTrait[j])
				{
					break;
				}
			}

			if (j==nTraitLen)
			{
				return i;
			}

		}

	}
	return 0;
}

/***************************************************/
/*         �Ƚ�������ʶ���ӳ�����������            */
/***************************************************/
BOOL MatchCode(byte *pSrc,byte *pDest,DWORD dwLen)
{
	for (DWORD i=0;i < dwLen;i++)
	{
		if (pDest[i] == 144)
		{
			continue;
		}
		if(pSrc[i] != pDest[i])
		{
			return FALSE;
		}
	}
	return TRUE;
}

/****************************************************/
/*     ��ȡEMap�����ļ������ҷ������������ָ��ͷ   */
/****************************************************/
Node *GetFileComCount(char *szFile,int *pnCount)
{
	HANDLE hFile = CreateFileA(szFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if ((int)hFile == -1)
	{
		return NULL;
	}
	DWORD dwFileSize = GetFileSize(hFile,NULL),dwReadSize;
	int nCount = dwFileSize / sizeof(Node);
	*pnCount = nCount;
	Node *pNode = new Node[nCount];
	memset(pNode,0,sizeof(Node)*nCount);
	ReadFile(hFile,pNode,dwFileSize,&dwReadSize,NULL);
	CloseHandle(hFile);
	return pNode;
}

/***************************************************/
/*          ö�ٳ���������֧�ֿ������             */
/***************************************************/
void EnumLibrary(DWORD *pCount)
{
	_Addtolist(0,1,"/*====================================================================*/");
	_Addtolist(0,1,"/*=====֧�ֿ�����������=============================================*/");
	_Addtolist(0,1,"/*====================================================================*/");
	pElib pelib;
	pCount = (DWORD*)(*pCount + g_RVASIZE);
	int nCount = *pCount;
	pCount++;
	DWORD *pFirstCom = (DWORD*) (*pCount+g_RVASIZE);
	
	for (int i=0;i<nCount;i++)
	{
		pelib = (pElib)(*pFirstCom + g_RVASIZE);
		_Addtolist(0,1,"----%s (%s)",pelib->szLibName+g_RVASIZE,pelib->szGuid+g_RVASIZE);

		DWORD *pCom = (DWORD*)(pelib->pFirstCom + g_RVASIZE);//ȡ��������׵�ַ
		int nNum = 0;BOOL bAly;
		char szEMapCode[255]={0};
		strcpy_s(szEMapCode,g_szEMap);
		strcat_s(szEMapCode,pelib->szGuid+g_RVASIZE);
		pNode p = GetFileComCount(szEMapCode,&nNum);
		pNode pTmp;
		if (p == NULL)
		{
			_Addtolist(0,1,"  !!δ�ҵ�EMap�������ļ�");
			bAly = FALSE;
		}
		else
		{
			bAly = TRUE;
		}
		for (int j=0;j<pelib->nComCount;j++)
		{
			pTmp = p;
			if (!bAly)
			{
				_Addtolist(*pCom,-1,"    --> %X (%s)",*pCom,"δ֪����");
				_Insertname(*pCom,NM_LABEL,"δ֪����");
			}
			else
			{
				for (int k=0;k<nNum;k++)
				{
					if (MatchCode((byte*)(*pCom+g_RVASIZE),pTmp->opcode,pTmp->nSize))
					{
						_Addtolist(*pCom,-1,"    --> %X (%s)",*pCom,pTmp->szName);
						_Insertname(*pCom,NM_LABEL,pTmp->szName);
						break;
					}
					pTmp++;
					if (k+1 == nNum)
					{
						_Addtolist(*pCom,1,"    --> %X (%s)",*pCom,"δ֪���� ����������Ǹ��߰汾����������");
						_Insertname(*pCom,NM_LABEL,"δ֪����");
					}
				}
			}

			pCom++;
		}

		pFirstCom++;
	}
	
}
/****************************************************/
/*   ö�ٳ���Api�������� ���ұ������������ַ       */
/****************************************************/
void EnumApiCom(DWORD *pApiCom)
{
	_Addtolist(0,1,"/*====================================================================*/");
	_Addtolist(0,1,"/*======Api�������===================================================*/"); 
	_Addtolist(0,1,"/*====================================================================*/");
	byte byUseApi[12] = {184,222,222,222,222,232,144,144,144,144,57,101}; 
	DWORD *dwCount,*pLib,*pCom; 
	dwCount = (DWORD*)(*pApiCom + 8 + g_RVASIZE);
	pLib = (DWORD*)(*pApiCom + 0xC + g_RVASIZE);
	pCom = (DWORD*)(*pApiCom + 0x10 + g_RVASIZE);

	pLib = (DWORD*)(*pLib + g_RVASIZE);
	pCom = (DWORD*)(*pCom + g_RVASIZE);
	char *Tmp,null[5]="NULL",*szApiName;

	for (DWORD i=0;i< *dwCount;i++)
	{
		Tmp = (char*)*pLib + g_RVASIZE;
		szApiName =(char*) *pCom + g_RVASIZE;
		if (Tmp[0]=='\0')
		{
			Tmp = null;
		}
		_Addtolist(0,1,"  ��:--> %s   Api:-> %s",Tmp,szApiName);
		memcpy(byUseApi+1,&i,4);
		DWORD result,dwTmp = 0,dwLen = g_SIZE;
		byte *pSrc = g_byVAddr;

		while (1)
		{
			result = Search_Bin(pSrc,byUseApi,dwLen,12);
			if (result==0)
			{
				break;
			}
			dwTmp+=result;
			_Addtolist(dwTmp+g_VA,-1,"    Api���õ�ַ��%X",dwTmp+g_VA);
			_Insertname(dwTmp+g_VA+5,NM_COMMENT,szApiName);
			pSrc+=result;pSrc+=12;
			dwLen-=result;dwLen-=12;
			dwTmp+=12;
		}
		pLib++;pCom++;
	}


	
}


/***************************************************/
/*		��ʼ����						           */
/***************************************************/
void EDebugStart()
{

	__asm{
		pushad;
		mov eax,0x0045a584;  //���log��־
		call eax;
		popad;
	}
	char szVA[10] = {0},szSIZE[10] = {0},*szTmp;
	DWORD dwVA,dwSIZE;
	ulong pBase,pSize;

	GetDlgItemTextA(g_hDialog,IDC_EDIT1,szVA,10);
	GetDlgItemTextA(g_hDialog,IDC_EDIT2,szSIZE,10);

	_Getdisassemblerrange(&pBase,&pSize);

	if (*szVA == NULL || *szSIZE == NULL)
	{
		t_module *S_md = _Findmodule(pBase);
		if (!S_md)
		{
			_Flash("�޷�ȷ��������С,�볢���ֶ������ڴ��ַ!");
			goto Exit;
		}
		dwVA = S_md->base;
		dwSIZE = S_md->size;
		goto Start;
	}

	if(strlen(szVA) > 8 || strlen(szSIZE) > 8)
	{
		_Flash("��ַ�������!");
		goto Exit;
	}
	dwVA = strtol(szVA,&szTmp,16);
	dwSIZE = strtol(szSIZE,&szTmp,16);

	
Start:
	g_VA = dwVA;
	SendMessageA(g_hDialog,WM_CLOSE,NULL,NULL);
	::ShowWindow(_Createlistwindow(),SW_MAXIMIZE);

	_Addtolist(0,1,"/**********************************************************************/");
	_Addtolist(0,1,"/*                            ->��ʼ����<-                            */         ������ַ:0x%X �ڴ��С:0x%X",dwVA,dwSIZE);
	_Addtolist(0,1,"/**********************************************************************/");

	g_dwVAddr = (DWORD)VirtualAlloc(0,dwSIZE,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	g_SIZE = dwSIZE;
	g_RVASIZE = g_dwVAddr - dwVA;
	_Readmemory((void*)g_dwVAddr,dwVA,dwSIZE,MM_RESILENT);
	g_byVAddr = (byte*)g_dwVAddr;

	memset(g_szEMap,0,255);
	GetCurrentDirectoryA(255,g_szEMap);
	strcat_s(g_szEMap,"\\\\plugin\\EMap\\");

	char szMain[255] = {0};
	strcpy_s(szMain,g_szEMap);
	strcat_s(szMain,"Main");

	int i,result;
	Node *pNode = GetFileComCount(szMain,&i);

	for (int j=0;j<i;j++)
	{
		result = Search_Bin(g_byVAddr,pNode[j].opcode,dwSIZE,pNode[j].nSize);
		if (result)
		{
			result = result+pNode[j].nOffset+dwVA;
			_Addtolist(0,-1,"    %X -> %s",result,pNode[j].szName);
			_Insertname(result,NM_LABEL,pNode[j].szName);
		}
	}

	byte bySupLib[13] = {51,255,59,207,126,96,51,246,59,207,126,40,161};
	result = Search_Bin(g_byVAddr,bySupLib,dwSIZE,13);
	if (!result)
	{
		_Addtolist(0,1,"Ŀ���ƺ�Ϊ�������Գ���!");
		goto Exit;
	}
	result += g_dwVAddr;
	result -= 4;
	EnumLibrary((DWORD*)result);
	EnumApiCom((DWORD*)result);

	_Addtolist(0,1,"/**********************************************************************/");
	_Addtolist(0,1,"/*                           ->��������<-                             */");
	_Addtolist(0,1,"/**********************************************************************/");
	_Addtolist(0,1,"Bug����:79884260 @qq.com");
	_Addtolist(0,1,"VERSION : E-Debug 2.0");
Exit:

	ExitThread(0);
}


 
