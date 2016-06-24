#pragma once
#include "DX11Wnd.h"
#include <atlbase.h>
#include "CommonIncludes.h"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#pragma warning(push)
// warning C4348: 'boost::spirit::terminal<...>::result_helper': redefinition of default parameter: parameter 3, 4
#pragma warning(disable: 4348)
#include <boost/spirit/include/qi.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "afxcmn.h"
#include "afxwin.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "DBOperations.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include <sys/stat.h>
#pragma warning(pop)

using namespace std;
using namespace boost::filesystem;

class CIndexerView : public CFormView
{
protected:
	CIndexerView();
	DECLARE_DYNCREATE(CIndexerView)
	DECLARE_MESSAGE_MAP()
public:
	CIndexerDoc* GetDocument() const;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CIndexerView();
	void DoDataExchange(CDataExchange * pDX);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DX11Wnd* DirectWnd;
	enum { IDD = IDD_INDEXER_FORM };
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonexpand();
	wstring m_strFolderPath;
	wstring m_lastPath;
	afx_msg void OnBnClickedButtoncollapse();
	afx_msg void OnBnClickedButtonfolder();
	CListCtrl m_listResult;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_radioButtons;
	CStatic m_PictureControl;
	int m_radioButtonsView;
	afx_msg void OnBnClickedButton1();
	CRichEditCtrl m_richEditSearch;
	afx_msg void OnBnClickedRadio2d();
	afx_msg void OnBnClickedRadio3d();
	string ToUtf8Str(const std::wstring & wstr);
	wstring toUtf8Wstr(const std::string & str);
	bool FileExists(const std::string & filename);
	void ReadSTL(std::string const & path_fb2, std::string const & path_stl, std::string const & solidName);
	void OnLButtonDown(UINT nFlags, CPoint point);
	CTreeCtrl m_tree1;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
private:
	std::vector<CString> ItemsNames;
	std::map<CString, CString> Items;
	std::unordered_map<string, bool> filesInDb;
	std::vector<wstring> resultFiles;
	std::vector<path> pathsToSearch;
	void LoadFilesBuildDB(const wpath & dir_path, bool *isFound, wpath* itdParent, CIndexerView* pDlg, bool isFirstLoop = true);
	void LoadItemsFromXml(const std::string &filename, const std::string &itdParent, std::string children, string item, int type,
		string(*getString)(boost::property_tree::ptree::value_type *v, string parent));
	void CheckFilesInDB();
	HTREEITEM FindItem(HTREEITEM hRoot, vector<wstring>* itemsInDb);
	void LoadCorrectFile(const std::string & filename, const std::string rootFile, int type);
	void LoadITDFile(const std::string& filename);
	void InsertFileInDB(const std::string &filename, std::string date, const std::string rootFile, int type);
	void SearchDirectories(std::vector<path>* directories, bool * isFound, path * itdParent, bool * localIsFound, CIndexerView * pDlg, bool isFirstLoop = true);
	void GetType(const path *p, bool * isFileOk, int *type, path *itdParent);
	void UpdateFileInDB(int type, string id, const std::string & filename, std::string date, const std::string rootFile);
	void SetBitmap(const wchar_t* filePath);
	void GetParams(std::string *text, std::vector<string> *keys, std::vector<string> *values);
	HTREEITEM FindItem(const CString& name, CTreeCtrl& tree, HTREEITEM hRoot);
	int GetSelectedItem(CListCtrl *plctrl);
	bool Find_file(const path& dir_path, const path& file_name, path& path_found);
	void AddResults(wstring type, vector<vector<string>> *result);
	void GetValues(std::string *text, std::vector<string> *values);
	void GetKeysFixture(std::vector<string> *keys);
	void GetKeysToolblock(std::vector<string> *keys);
	string GetQuery(std::vector<string>* keys, std::vector<string>* values);
	void ToggleTreeNode(HTREEITEM hItem, UINT toggleType);
	void OnRender();
	vector<string> keysFixture;
	vector<string> keysToolblock;
	afx_msg LRESULT OnTreeUpdate(WPARAM, LPARAM);
	UINT NonStaticThreadDB(LPVOID param);
	static UINT ThreadDB(LPVOID param);
public:
	CButton m_checkBoxScaling;
	afx_msg void OnBnClickedCheck1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CProgressCtrl m_progressBar;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_folderButton;
};

