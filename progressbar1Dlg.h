// progressbar1Dlg.h : header file
//

#pragma once
#include "afxcmn.h"

#include "ProgressCtrlWithTimer.h"
#include "ProgressThread.h"

// Cprogressbar1Dlg dialog
class Cprogressbar1Dlg : public CDialog
{
// Construction
public:
	Cprogressbar1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROGRESSBAR1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	CProgressCtrlWithTimer p1;
	CProgressCtrl p2;
	CProgressThread* pt;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnActivate( UINT, CWnd*, BOOL );

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton3();
};
