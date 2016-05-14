
// MFCApplication5Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxdialogex.h"
#include "afxcmn.h"
#include "stdafx.h"
#include "MFCApplication5.h"
#include "FolderDlg.h"
#include "sqlite3.h"
#include "CommonIncludes.h"
using namespace boost::filesystem;
using namespace std;

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
	void LoadFilesBuildDB( const path & dir_path, HTREEITEM *root, bool *isFound,path* itdParent);
	void LoadItemsFromXml(const std::string &filename, const std::string &itdParent, std::string children, string item, int type, 
		string(*getString)(boost::property_tree::ptree::value_type *v,string parent));
	void LoadCorrectFile(const std::string & filename, const std::string rootFile, int type);
	void LoadITDFile(const std::string& filename);
	void InsertFileInDB(const std::string &filename, std::string date, const std::string rootFile, int type);
	void SearchDirectories(std::vector<path> *directories, bool *isFound, HTREEITEM *root, path* itdParent, bool *localIsFound);
	void GetType(const path *p, bool * isFileOk, int *type, path *itdParent);
	void UpdateFileInDB(int type, string id, const std::string & filename, std::string date, const std::string rootFile);
	std::vector<CString> SplitCString(CString text, LPCWSTR separator);	
	DECLARE_MESSAGE_MAP()
public:
	CArray<double, double> Values;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton1();
	CButton m_fileButton;
	CStatic m_PictureControl;
	CTreeCtrl m_tree;
	afx_msg void OnTvnItemChangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CRichEditCtrl m_richEditSearch;
	CButton m_searchButton;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeRichedit22();
};
