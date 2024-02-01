
// CodeMakeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CCodeMakeDlg �Ի���
class CCodeMakeDlg : public CDialogEx
{
// ����
public:
	CCodeMakeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CODEMAKE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void AddMessage(char *str);
	afx_msg void EnumCommand(char *szFile);
	afx_msg void MakeCommand(char *szFile);
	HWND hEdit;
	HWND hStc2;
	HWND hStc3;
	BOOL m_check;
	CProgressCtrl m_Progress;
};
