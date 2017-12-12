
// FivechClientDlg.h : ͷ�ļ�
//

#pragma once
#include "Network.h"
#include "Board.h"
#include "resource.h"
// CFivechClientDlg �Ի���
class CFivechClientDlg : public CDialogEx
{
// ����
public:
	CFivechClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FIVECHCLIENT_DIALOG };

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
	afx_msg void OnBnClickedConnect();
	afx_msg LRESULT OnNetEvent(WPARAM wParam, LPARAM lParam);
	int p;
	afx_msg void OnBnClickedBtnBlack();
	afx_msg void OnBnClickedBtnWhite();
};
