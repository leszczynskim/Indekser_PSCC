
// MFCApplication5Dlg.cpp : implementation file
//
#include "stdafx.h"
#include "MFCApplication5Dlg.h"
#include "Fixture.h"
#include "sqlite3.h"
#include <chrono>
#include <locale>
#include <codecvt>
#pragma warning(disable : 4996)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace boost::filesystem;

std::vector<CString> ItemsNames;
std::map<CString, CString> Items;
CString last;
int index = 0;
LPCTSTR m_strFolderPath;
const char* CMFCApplication5Dlg::DATABASE_NAME = "IndexerDB.db";

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
	DDX_Control(pDX, IDC_RICHEDIT22, m_richEditSearch);
	DDX_Control(pDX, IDC_BUTTON2, m_searchButton);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFCApplication5Dlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication5Dlg::OnBnClickedButton1)
	ON_NOTIFY(TVN_SELCHANGED, 0x1221, &CMFCApplication5Dlg::OnTvnItemChangedTree1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication5Dlg::OnBnClickedButton2)
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
		TVS_SHOWSELALWAYS | TVS_TRACKSELECT,
		CRect(690, 10, 1005, 500), this, 0x1221);

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

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

bool hasEnding(std::string const &fullString, std::string const &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

void CMFCApplication5Dlg::LoadFilesBuildDB(const path & dir_path, HTREEITEM *root, bool *isFound, path* itdParent)
{
	if (!exists(dir_path))
		return;
	directory_iterator end_itr;
	bool localIsFound = false;
	std::vector<path> directories;
	for (directory_iterator itr(dir_path); itr != end_itr; ++itr)
	{
		if (is_directory(itr->status())) 
			directories.push_back(itr->path());
		if (itr->path().extension() == ".bmp")
		{
			localIsFound = true;
			*isFound = true;
			if (!root) m_tree.InsertItem(itr->path().filename().c_str(), TVI_ROOT);
			else m_tree.InsertItem(itr->path().filename().c_str(), *root);
		}
		else if (itr->path().extension() == ".ITD" || itr->path().filename() == "Fixtures.xml" || itr->path().filename() == "Toolblocks.xml")
		{
			if (itr->path().extension() == ".ITD") *itdParent = itr->path();
			bool isNotModified,doesExist;
			string date = GetDateOfModification(itr->path(), &isNotModified,&doesExist);
			if (!doesExist)
			{
				std::vector<std::vector<string>> result;
				using convert_typeX = std::codecvt_utf8<wchar_t>;
				std::wstring_convert<convert_typeX, wchar_t> converter;
				std::wstring wide = converter.from_bytes(date);
				wstring comm(L"INSERT INTO FILETABLE (filepath,dateofmod) VALUES ('");
				comm += itr->path().c_str();
				comm += L"','" + wide + L"');";
				string s = converter.to_bytes(comm);
				ExecuteCommand(s.c_str(), NULL);
			}
			else if (!isNotModified)
			{
			}
		}
	}
	for (path p:directories)
	{
		*isFound = false;
		HTREEITEM rootTmp = NULL;
		if (!root)
			rootTmp = m_tree.InsertItem(p.filename().c_str(), TVI_ROOT);
		else
			rootTmp = m_tree.InsertItem(p.filename().c_str(), *root);
		LoadFilesBuildDB(p, &rootTmp, isFound,itdParent);
		if (!(*isFound))
		{
			m_tree.DeleteItem(rootTmp);
			if (localIsFound) *isFound = true;
		}
	}
}

void CMFCApplication5Dlg::OnLbnSelchangeList1()
{
	//int i = m_Values.GetCaretIndex();
	int i = 0;
	CString tmp = Items[ItemsNames[i]];
	HBITMAP startBitmap = (HBITMAP)LoadImage(NULL, tmp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_PictureControl.SetBitmap(startBitmap);
	index = 0;
}

void CMFCApplication5Dlg::OnBnClickedButton1()
{
	CreateDB();
	CFolderDialog dlg(_T("Root folder is C:\ "), NULL, this);
	dlg.SetRootFolder(_T("C:\input_do_ineksera"));
	LPCTSTR m_strDisplayName;
	m_strFolderPath = L"C:\\input_do_ineksera";
	bool b = false;
	path p;
	LoadFilesBuildDB(m_strFolderPath, NULL, &b,&p);
	/*if( dlg.DoModal() == IDOK  )
	{
	m_strFolderPath = dlg.GetFolderPath();
	LoadFiles(m_strFolderPath, NULL, &b);
	}*/
}

void CMFCApplication5Dlg::OnTvnItemChangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
	// TODO: Add your control notification handler code here
	wstring finalString;// = m_strFolderPath;
	HTREEITEM a = m_tree.GetSelectedItem();
	CString s = m_tree.GetItemText(a);
	finalString += LPCTSTR("\\");
	finalString += (LPCTSTR)s;

	int i = 0;
	while (a != NULL)
	{
		a = m_tree.GetParentItem(a);
		s = m_tree.GetItemText(a);
		auto tmp = finalString;
		finalString = LPCTSTR("\\") + s;
		finalString += tmp;
		i++;
	}
	auto tmp = finalString;
	finalString.clear();
	finalString = CString(m_strFolderPath);// m_strFolderPath;
	finalString += tmp;
	CBitmap m_bitmap;
	HBITMAP startBitmap = (HBITMAP)LoadImage(NULL, finalString.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (startBitmap != NULL)
	{
		//CBitmap bitmap;
		//CRect *rect = new CRect(0, 0, 500, 300);

		//m_PictureControl.GetClientRect(rect);

		//bitmap.Attach(startBitmap);

		//m_PictureControl.SetBitmap(bitmap);

		//// Now it would be supposed to fit the control:
		//CDC *pDC = m_PictureControl.GetDC();
		//CDC m_DC;

		//m_DC.CreateCompatibleDC(pDC);
		//m_DC.SelectObject(&bitmap);

		//pDC->StretchBlt(0, 0, rect->Width(), rect->Height(), &m_DC, 0, 0, 67, 37, SRCCOPY);

		m_bitmap.Attach(startBitmap);
		m_PictureControl.SetBitmap(m_bitmap);
	}
}

std::vector<Fixture> CMFCApplication5Dlg::LoadFixtures(const std::string &filename)
{
	std::vector<Fixture> fixtures;
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(filename, pt);

	BOOST_FOREACH(ptree::value_type &v, pt.get_child("GC_ITFixtureData.fixtures"))
	{
		if (v.first == "GC_ITFixture")
		{
			Fixture f;
			f.make = v.second.get<std::string>("make");
			f.file = v.second.get<string>("file");
			f.name = v.second.get<string>("name");
			f.fixture_type = v.second.get<int>("fixture_type");
			f.user_type = v.second.get_optional<int>("user_type");
			f.metric = v.second.get<int>("metric");
			f.match = v.second.get<int>("match");
			f.num_sim_files = v.second.get<int>("num_sim_files");
			f.chuck_width = v.second.get<float>("chuck_width");
			f.gb_depth = v.second.get<float>("gb_depth");
			f.gb_pullback_dist = v.second.get<float>("gb_pullback_dist");
			fixtures.push_back(f);
			// add to db
		}
	}
	return fixtures;
}

void CMFCApplication5Dlg::CreateDB() {
	std::ifstream fin;
	fin.exceptions(ios::badbit | ios::failbit | ios::eofbit);
	fin.open("script.txt");
	std::string contents((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	auto x = contents.c_str();
	fin.close();
	ExecuteCommand(contents.c_str(),NULL);
}

sqlite3* CMFCApplication5Dlg::GetConnection()
{
	int  rc;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE_NAME, &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return NULL;
	}
	return db;
}

int command_callback(void * p_data, int num_fields, char ** p_fields, char ** p_col_names)
{
	std::vector<std::vector<string>>* records = static_cast<std::vector<std::vector<string>>*>(p_data);
	try {
		records->emplace_back(p_fields, p_fields + num_fields);
	}
	catch (...) {
		return 1;
	}
	return 0;
}
void CMFCApplication5Dlg::ExecuteCommand(const char *command, std::vector<std::vector<string>>* result)
{
	int  rc;
	char *zErrMsg = 0;
	sqlite3 *db = GetConnection();
	if (!result) rc = sqlite3_exec(db, command, NULL, 0, &zErrMsg);
	else rc = sqlite3_exec(db, command, command_callback, result, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);
}

string CMFCApplication5Dlg::GetDateOfModification(boost::filesystem::path p, bool *isModified, bool *doesExsist)
{
	std::time_t t = boost::filesystem::last_write_time(p);
	char buff[20];
	strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&t));
	std::vector<std::vector<string>> result;
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converter;
	wstring command(L"Select dateofmod from filetable where filepath='");
	command += p.c_str() + wstring(L"'");
	auto s = converter.to_bytes(command);
	ExecuteCommand(s.c_str(), &result);
	string date(buff);
	*doesExsist = result.size() != 0;
	*isModified = date != result[0][0];
	return date;
}

void CMFCApplication5Dlg::OnBnClickedButton2()
{
	CString text;
	m_richEditSearch.GetWindowTextW(text);
	vector<CString> lines = SplitCString(text, L"\n");
	for each (CString line in lines)
	{
		vector<CString> splittedLine = SplitCString(line, L"=");
		vector<CString> arguments = SplitCString(splittedLine[1], L";");
	}
}

vector<CString> CMFCApplication5Dlg::SplitCString(CString text, LPCWSTR separator)
{
	int index = 0;
	vector<CString> result;
	CString tmp;
	tmp = text.Tokenize(separator, index);
	while (tmp != "")
	{
		result.push_back(tmp);
		tmp = text.Tokenize(separator, index);
	}

	return result;
}