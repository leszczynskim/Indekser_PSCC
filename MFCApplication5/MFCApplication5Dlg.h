
// MFCApplication5Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxdialogex.h"
#include "afxcmn.h"
#include "stdafx.h"
#include "MFCApplication5.h"
#include "FolderDlg.h"
#include <vector>
#include <string.h>
#include <map>
#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include "Fixture.h"
#include "sqlite3.h"

using namespace boost::filesystem;


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
	void LoadFiles( const path & dir_path, HTREEITEM *root, bool *isFound);
	std::vector<Fixture> LoadFixtures(const std::string &filename);
	void CreateDB();
	void ExecuteCommand(char * command);
	sqlite3* GetConnection();
	
	DECLARE_MESSAGE_MAP()
public:
	CArray<double, double> Values;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton1();
	CButton m_fileButton;
	CStatic m_PictureControl;
	CTreeCtrl m_tree;
	afx_msg void OnTvnItemChangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSingleExpandTree3(NMHDR *pNMHDR, LRESULT *pResult);

	const static char* DATABASE_NAME;
	CRichEditCtrl m_richEditSearch;
	CButton m_searchButton;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeRichedit22();
};
