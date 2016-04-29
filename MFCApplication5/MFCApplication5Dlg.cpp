
// MFCApplication5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"
#include "FolderDlg.h"
#include <vector>
#include <string.h>
#include <map>
#include <boost/filesystem.hpp>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace boost::filesystem;

std::vector<CString> ItemsNames;
std::map<CString,CString> Items;
CString last;
int index = 0;

CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_fileButton);
	DDX_Control(pDX, IDC_PICTURE, m_PictureControl);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFCApplication5Dlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication5Dlg::OnBnClickedButton1)
	//ON_NOTIFY(TVN_ITEMCHANGED, 0x1221, &CMFCApplication5Dlg::OnTvnItemChangedTree1)
END_MESSAGE_MAP()


// CMFCApplication5Dlg message handlers

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    m_tree.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP |
		             TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
			 TVS_SINGLEEXPAND | TVS_SHOWSELALWAYS |  
			 TVS_TRACKSELECT,
		             CRect(690, 10, 1005, 500), this, 0x1221);
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void CMFCApplication5Dlg::Recurse(LPCTSTR pstr)
{
   CFileFind finder;
   CString strWildcard(pstr);
   strWildcard += _T("\\*.ITD");
   BOOL bWorking, isITD = finder.FindFile(strWildcard);
   
	HTREEITEM hTree = NULL;
	if(!isITD)
	{
		strWildcard = pstr;
		strWildcard += _T("\\*.*");
		bWorking = finder.FindFile(strWildcard);

		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDots())
				continue;

			CString ext = finder.GetFileName().Right(3);
			if(ext == "bmp" && !last.IsEmpty())
			{
				CString tmp = last + ":" + finder.GetFileTitle();
				Items.insert(pair<CString,CString>(tmp, finder.GetFilePath()));
				m_tree.InsertItem(tmp,hTree);
				
			}
			if (finder.IsDirectory())
			{
				hTree = m_tree.InsertItem(finder.GetFileTitle(),TVI_ROOT);
				CString str = finder.GetFilePath();
				Recurse(str);
			}
		}
	}
   while (bWorking)
   {
      bWorking = finder.FindNextFile();
	  if (finder.IsDots())
         continue;
	  last = finder.GetFileTitle();
   }


   
   finder.Close();
}

void CMFCApplication5Dlg::LoadFiles( const path & dir_path, HTREEITEM *root, bool *isFound )
{
	if ( !exists( dir_path ) ) 
		return;
	directory_iterator end_itr;
	bool localIsFound = false;
	for ( directory_iterator itr( dir_path ); itr != end_itr; ++itr )
	{
		if ( is_directory(itr->status()) )
		{
			*isFound = false;
			HTREEITEM rootTmp = NULL;
			if(!root)
				rootTmp = m_tree.InsertItem(itr->path().filename().c_str(), TVI_ROOT);
			else
				rootTmp = m_tree.InsertItem(itr->path().filename().c_str(), *root);
			LoadFiles( itr->path(), &rootTmp, isFound);
			if (!(*isFound))
			{
				m_tree.DeleteItem(rootTmp);
				if(localIsFound)
					*isFound = true;
			}
		}
		if( itr->path().extension() == ".bmp" )
		{
			localIsFound = true;
			*isFound = true;
			if (!root)
				m_tree.InsertItem(itr->path().filename().c_str(), TVI_ROOT);
			else
				m_tree.InsertItem(itr->path().filename().c_str(), *root);
		}
	}
}

void CMFCApplication5Dlg::OnLbnSelchangeList1()
{
	//int i = m_Values.GetCaretIndex();
	int i =0;
	CString tmp = Items[ItemsNames[i]];
	HBITMAP startBitmap = (HBITMAP)LoadImage(NULL, tmp, IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
	m_PictureControl.SetBitmap(startBitmap);
	index = 0;
}

void CMFCApplication5Dlg::OnBnClickedButton1()
{
	CFolderDialog dlg( _T( "Root folder is C:\ " ), NULL, this );
    dlg.SetRootFolder( _T( "C:\input_do_ineksera" ));
	LPCTSTR m_strFolderPath;
	LPCTSTR m_strDisplayName;
    if( dlg.DoModal() == IDOK  )
    {    
		m_strFolderPath = dlg.GetFolderPath();
		bool b = false;
		LoadFiles(m_strFolderPath, NULL, &b);
    }
}

void CMFCApplication5Dlg::OnTvnItemChangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM a = m_tree.GetSelectedItem();
	int i = 0;
	while (m_tree.GetParentItem(a) == nullptr)
	{
		a = m_tree.GetParentItem(a);
		i++;
	}
	*pResult = 0;
}
