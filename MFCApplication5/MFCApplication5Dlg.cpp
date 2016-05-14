
// MFCApplication5Dlg.cpp : implementation file
//
#include "stdafx.h"
#include "MFCApplication5Dlg.h"
#include "Fixture.h"
#include "sqlite3.h"
#include "DBOperations.h"
#include <chrono>
#include <locale>
#include <codecvt>
#include <unordered_map>
#ifdef _DEBUG
#define new DEBUG_NEW
#define FilePair(x, y) std::make_pair(std::string(x),bool(y))
#endif

using namespace std;
using namespace boost::filesystem;

std::vector<CString> ItemsNames;
std::map<CString, CString> Items;
std::unordered_map<string, bool> filesInDb;
CString last;
int index = 0;
LPCTSTR m_strFolderPath;


string GetFixture(boost::property_tree::ptree::value_type *v, string itdParentId)
{
	ostringstream ss;
	auto x = v->second.get_optional<int>("user_type");
	ss << x;
	string s = x.is_initialized() ? ss.str() : "NULL";
	ss.clear();
	ss.str("");
	ss << "insert into Fixture (make,file,name,fixture_type,user_type,metric,match,num_sim_files,chuck_width,gb_depth,gb_pullback_dist,idt_id) values('"
		<< v->second.get<std::string>("make") << "','" << v->second.get<string>("file")
		<< "','" << v->second.get<string>("name") << "'," << v->second.get<int>("fixture_type")
		<< "," << s << "," << v->second.get<int>("metric")
		<< "," << v->second.get<int>("match") << "," << v->second.get<int>("num_sim_files")
		<< "," << v->second.get<float>("chuck_width") << "," << v->second.get<float>("gb_depth")
		<< "," << v->second.get<float>("gb_pullback_dist") << "," << itdParentId << ");";
	return ss.str();
}

string GetToolblock(boost::property_tree::ptree::value_type *v, string itdParentId)
{
	ostringstream ss;
	auto x = v->second.get_optional<string>("block_types");
	ss << x;
	string s = x.is_initialized() ? ss.str() : "NULL";
	ss.clear();
	ss.str("");
	x = v->second.get_optional<string>("shank_sizes");
	ss << x;
	string s1 = x.is_initialized() ? ss.str() : "NULL";
	ss.clear();
	ss.str("");
	ss << "insert into Toolblock (make,file,name,metric,offset_x,offset_y,offset_z,num_orientations,match,num_sim_files,tool_pos,\
		cs,cs_name,match_tool_pos,block_types,shank_sizes,default_orient,default_cs,idt_id) values('"
		<< v->second.get<std::string>("make") << "','" << v->second.get<string>("file") << "','"
		<< v->second.get<string>("name") << "'," << v->second.get<int>("metric") << ","
		<< v->second.get<bool>("offset_x") << "," << v->second.get<bool>("offset_y") << ","
		<< v->second.get<bool>("offset_z") << "," << v->second.get<int>("num_orientations") << ","
		<< v->second.get<int>("match") << "," << v->second.get<int>("num_sim_files") << ",'";
	using boost::property_tree::ptree;
	auto i = v->second.get_child("tool_pos");
	BOOST_FOREACH(ptree::value_type &i, v->second.get_child("tool_pos"))
	{
		for (auto iter = i.second.get_child("matrix").begin(); iter != i.second.get_child("matrix").end(); iter++)
			ss << iter->second.data() << ";";
		ss << "',";
		ss << i.second.get<int>("cs") << ",'";
		ss << i.second.get<string>("cs_name") << "',";
		break;
	}
	ss << v->second.get<int>("match_tool_pos") << ",'" << s << "','" << s1 << "',"
	<< v->second.get<int>("default_orient") << ",'"	<< v->second.get<string>("default_cs") 
	<< "',"	<< itdParentId << ");";
	return ss.str();
}

void CMFCApplication5Dlg::LoadItemsFromXml(const std::string & filename, const std::string & itdParent, string children,
	string item, int type, string(*getString)(boost::property_tree::ptree::value_type *v, string parent))
{
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(filename, pt);
	std::vector<std::vector<string>> res;
	string com = "select id from filetable where filepath='" + itdParent + "' or filepath='" + filename + "'";
	DBOperations::ExecuteCommand(com.c_str(), &res);
	string itdParentId = res[0][0], file_id = res[1][0];
	BOOST_FOREACH(ptree::value_type &v, pt.get_child(children))
	{
		if (v.first != item) continue;
		string s = getString(&v, itdParentId);
		int id;
		DBOperations::ExecuteCommand(s.c_str(), NULL, true, &id);
		ostringstream ss;
		ss << "Insert into file_object (file_id,item_id,typ_id) values(" << file_id << "," << id << "," << type << ");";
		DBOperations::ExecuteCommand(ss.str().c_str(), NULL);
	}
}

void CMFCApplication5Dlg::LoadCorrectFile(const std::string & filename, std::string date, const std::string rootFile, int type)
{
	switch (type)
	{
	case FIXTURE:
		LoadItemsFromXml(filename, rootFile, "GC_ITFixtureData.fixtures", "GC_ITFixture", FIXTURE, GetFixture);
		break;
	case TOOLBLOCK:
		LoadItemsFromXml(filename, rootFile, "GC_ITBlockData.blocks", "GC_ITBlock", TOOLBLOCK, GetToolblock);
		break;
	case ITD:
		break;
	}
}

void CMFCApplication5Dlg::InsertFileInDB(const std::string & filename, std::string date, const std::string rootFile, int type)
{
	string comm("INSERT INTO FILETABLE (filepath,dateofmod) VALUES ('");
	comm += filename + "','" + date + "');";
	DBOperations::ExecuteCommand(comm.c_str(), NULL);
	LoadCorrectFile(filename, date, rootFile, type);
}

void CMFCApplication5Dlg::SearchDirectories(std::vector<path> *directories, bool *isFound, HTREEITEM *root, path* itdParent, bool *localIsFound)
{
	for (path p : *directories)
	{
		*isFound = false;
		HTREEITEM rootTmp = NULL;
		if (!root)
			rootTmp = m_tree.InsertItem(p.filename().c_str(), TVI_ROOT);
		else
			rootTmp = m_tree.InsertItem(p.filename().c_str(), *root);
		LoadFilesBuildDB(p, &rootTmp, isFound, itdParent);
		if (!(*isFound))
		{
			m_tree.DeleteItem(rootTmp);
			if (*localIsFound) *isFound = true;
		}
	}
}

void CMFCApplication5Dlg::GetType(const path *p, bool * isFileOk, int *type, path *itdParent)
{
	if (p->extension() == ".ITD")
	{
		*itdParent = *p;
		type = ITD;
		*isFileOk = true;
	}
	else if (p->filename() == "Fixtures.xml")
	{
		*type = FIXTURE;
		*isFileOk = true;
	}
	else if (p->filename() == "Toolblocks.xml")
	{
		*type = TOOLBLOCK;
		*isFileOk = true;
	}
}

void CMFCApplication5Dlg::LoadFilesBuildDB(const path & dir_path, HTREEITEM *root, bool *isFound, path* itdParent)
{
	if (!exists(dir_path)) return;
	directory_iterator end_itr;
	bool localIsFound = false;
	std::vector<path> directories;
	for (directory_iterator itr(dir_path); itr != end_itr; ++itr)
	{
		bool b = false;
		int type = 0;
		string id;
		if (is_directory(itr->status())) directories.push_back(itr->path());
		if (itr->path().extension() == ".bmp")
		{
			localIsFound = true;
			*isFound = true;
			if (!root) m_tree.InsertItem(itr->path().filename().c_str(), TVI_ROOT);
			else m_tree.InsertItem(itr->path().filename().c_str(), *root);
		}
		GetType(&(itr->path()), &b, &type, itdParent);
		if (!b) continue;
		auto x = itr->path().string();
		filesInDb[x] = true;
		bool isModified, doesExist;
		string date = DBOperations::GetDateOfModification(itr->path(), &isModified, &doesExist, &id);
		if (!doesExist)
		{
			InsertFileInDB(x, date, itdParent->string(), type);
		}
		else if (isModified)
		{
			UpdateFileInDB(type, id, x, date, itdParent->string());
		}
	}
	SearchDirectories(&directories, isFound, root, itdParent, &localIsFound);
}

void CMFCApplication5Dlg::UpdateFileInDB(int type, string id, const std::string & filename, std::string date, const std::string rootFile)
{
	string s = "fixture";
	switch (type)
	{
	case ITD:
		s = "itd";
		break;
	case TOOLBLOCK:
		s = "toolblock";
		break;
	}
	ostringstream ss;
	ss << "delete from "<< s <<" where id in( select f.id from " << s << " f join file_object fo on fo.item_id = f.id\
		join filetable ft on ft.id = fo.file_id	where ft.id = " << id << "); delete from file_object where file_id = " << id << ";"
		<< "update filetable set dateofmod = '" << date << "' where id = " << id << ";";
	DBOperations::ExecuteCommand(ss.str().c_str(), NULL);
	LoadCorrectFile(filename, date, rootFile, type);
}

CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent)
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

HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
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
	DBOperations::Create("script.txt",&filesInDb);
	CFolderDialog dlg(_T("Root folder is C:\ "), NULL, this);
	dlg.SetRootFolder(_T("C:\input_do_ineksera"));
	LPCTSTR m_strDisplayName;
	m_strFolderPath = L"C:\\input_do_ineksera";
	bool b = false;
	path p;
	LoadFilesBuildDB(m_strFolderPath, NULL, &b,&p);
	for (auto &x : filesInDb)
	{
		if (!x.second)
		{
			//usunac
		}
	}
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