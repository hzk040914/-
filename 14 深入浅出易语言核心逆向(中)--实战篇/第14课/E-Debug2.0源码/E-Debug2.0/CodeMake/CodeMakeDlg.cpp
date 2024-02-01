
// CodeMakeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CodeMake.h"
#include "CodeMakeDlg.h"
#include "afxdialogex.h"
#include "Elib.h"

#define BEA_ENGINE_STATIC  /* specify the usage of a static version of BeaEngine */
#define BEA_USE_STDCALL    /* specify the usage of a stdcall version of BeaEngine */
#include "BeaEngine.h"
#pragma comment(lib,"BeaEngine.lib")

typedef struct {
	char szName[40];
	int  nSize;
	int  nOffset;
	byte opcode[80];
}Node,*PNode;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCodeMakeDlg �Ի���




CCodeMakeDlg::CCodeMakeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCodeMakeDlg::IDD, pParent)
	, m_check(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodeMakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_check);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(CCodeMakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CCodeMakeDlg ��Ϣ�������

BOOL CCodeMakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	GetDlgItem(IDC_STATIC2,&hStc2);
	GetDlgItem(IDC_STATIC3,&hStc3);
	GetDlgItem(IDC_EDIT1,&hEdit);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCodeMakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCodeMakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCodeMakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCodeMakeDlg::AddMessage(char *str)
{
	char *huan = "\r\n";
	::SendMessageA(hEdit,EM_SETSEL,88888,88888);
	::SendMessageA(hEdit,EM_REPLACESEL,NULL,LPARAM(str));
	::SendMessageA(hEdit,EM_REPLACESEL,NULL,LPARAM(huan));
}


void CCodeMakeDlg::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);
	UINT count;
	char szFilePath[255] = {0};
	count = DragQueryFileA(hDropInfo,0,szFilePath,255);
	CString str(szFilePath);
	if (strcmp(".fne",str.Right(4)) == 0)
	{
		::SetWindowTextA(hStc2,szFilePath);
		MakeCommand(szFilePath);
	}
	else if (m_check)
	{
		EnumCommand(szFilePath);
	}
	else
	{
		AfxMessageBox("������ȷ��.fne�ļ�!");
	}
	
	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}

void CCodeMakeDlg::MakeCommand(char *szFile)
{
	::SetWindowTextA(hEdit,"");
	char szFile2[255] = {0},szCurPath[255] = {0};
	GetCurrentDirectoryA(255,szCurPath);
	strcat_s(szCurPath,"\\");

	strncpy_s(szFile2,szFile,strlen(szFile)-4);
	strcat_s(szFile2,"2.fne");
	CopyFileA(szFile,szFile2,FALSE);

	LIB_INFO *pLibinfo = NULL,*pLibinfo2 = NULL;
	HMODULE hLib = LoadLibraryA(szFile);
	HMODULE hLib2 = LoadLibraryA(szFile2);
	DWORD dwNewInf = (DWORD)GetProcAddress(hLib,FUNCNAME_GET_LIB_INFO);
	_asm{
		call dwNewInf;
		mov pLibinfo,eax;
	}
	DWORD dwNewInf2 = (DWORD)GetProcAddress(hLib2,FUNCNAME_GET_LIB_INFO);
	_asm{
		call dwNewInf2;
		mov pLibinfo2,eax;
	}
	strcat_s(szCurPath,pLibinfo->m_szGuid);
	CString str;
	str.Format("%s ( %s ) %d������",pLibinfo->m_szName,pLibinfo->m_szGuid,pLibinfo->m_nCmdCount);
	::SetWindowTextA(hStc3,str.GetBuffer(NULL));

	CMD_INFO *pCmdInfo = pLibinfo->m_pBeginCmdInfo;

	DWORD *pCmdFunc = (DWORD*)pLibinfo->m_pCmdsFunc;
	DWORD *pCmdFunc2 = (DWORD*)pLibinfo2->m_pCmdsFunc;

	m_Progress.SetRange(0,pLibinfo->m_nCmdCount-1);

	DWORD pFunc1,pFunc2;
	DISASM MyAsm1,MyAsm2;
	Node *pNode = new Node[pLibinfo->m_nCmdCount];
	ZeroMemory(pNode,sizeof(Node)*pLibinfo->m_nCmdCount);

	byte byNull[10]={144,144,144,144,144,144,144,144,144,144};
	int len,j,k=0;

	for (int i=0;i<pLibinfo->m_nCmdCount;i++)
	{

		if (*pCmdFunc)
		{
			byte *pTmp = pNode[k].opcode;
			strcpy_s(pNode[k].szName,pCmdInfo->m_szName);
			j=0;
			pFunc1 = (DWORD)*pCmdFunc;
			pFunc2 = (DWORD)*pCmdFunc2;
			do 
			{
				memset(&MyAsm1,0,128);memset(&MyAsm2,0,128);
				MyAsm1.EIP = (UIntPtr)pFunc1;
				MyAsm2.EIP = (UIntPtr)pFunc2;
				len = Disasm(&MyAsm1);Disasm(&MyAsm2);
				if (j+len > 80)
				{
					break;
				}
				if(strcmp(MyAsm1.CompleteInstr,MyAsm2.CompleteInstr) != 0 && !strstr(MyAsm1.CompleteInstr,"j"))
				{
					memcpy(pTmp,byNull,len);
					pTmp+=len;
				}
				else
				{
					memcpy(pTmp,(void*)pFunc1,len);
					pTmp+=len;
				}

				pFunc1+=len;pFunc2+=len;
				j+=len;

			} while (strstr(MyAsm1.CompleteInstr,"ret")==NULL);

			pNode[k].nSize = j;

			k++;
			str.Format("%d.%s -> %X",k,pCmdInfo->m_szName,*pCmdFunc);
			AddMessage(str.GetBuffer(NULL));

		}

		pCmdInfo++;pCmdFunc++;pCmdFunc2++;

		m_Progress.SetPos(i);
	}
	DWORD pBytesWritten=0;
	HANDLE hFile = CreateFileA(szCurPath,GENERIC_WRITE,NULL,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	WriteFile(hFile,pNode,sizeof(Node) * k,&pBytesWritten,NULL);
	CloseHandle(hFile);
	str.Format("����EMap�������ļ��ɹ� --> %s",szCurPath);
	AddMessage(str.GetBuffer(0));

	FreeLibrary(hLib);
	FreeLibrary(hLib2);
	while (!DeleteFileA(szFile2))
	{
		NULL;
	}	
}

void CCodeMakeDlg::EnumCommand(char *szFile)
{
	::SetWindowTextA(hEdit,"");

	HANDLE hFile = CreateFileA(szFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD dwFileSize = GetFileSize(hFile,NULL),dwReadSize;
	int nCount = dwFileSize / sizeof(Node);
	CString str;

	Node *pNode = new Node[nCount];
	memset(pNode,0,sizeof(Node)*nCount);

	ReadFile(hFile,pNode,dwFileSize,&dwReadSize,NULL);
	for(int i=0;i<nCount;i++)
	{
		str.Format("%d.%s  ->  nSize = %d    nOffset = %d",i+1,pNode[i].szName,pNode[i].nSize,pNode[i].nOffset);
		AddMessage(str.GetBuffer(NULL));
	}
	CloseHandle(hFile);

}
