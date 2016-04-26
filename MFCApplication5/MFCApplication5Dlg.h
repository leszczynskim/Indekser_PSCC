
// MFCApplication5Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxdialogex.h"


// CMFCApplication5Dlg dialog
class CMFCApplication5Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication5Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION5_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void Recurse(LPCTSTR);

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_Values;
	CArray<double, double> Values;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton1();
	CButton m_fileButton;
	CStatic m_PictureControl;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
