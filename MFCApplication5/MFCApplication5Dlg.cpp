
// MFCApplication5Dlg.cpp : implementation file
//
#include "stdafx.h"
#include "MFCApplication5Dlg.h"
#include "sqlite3.h"
#include "DBOperations.h"
#include <atlbase.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace boost::filesystem;

std::vector<CString> ItemsNames;
std::map<CString, CString> Items;
std::unordered_map<string, bool> filesInDb;
std::vector<wstring> resultFiles;
std::vector<path> pathsToSearch;
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
	ss << "insert into Fixture (make,file,name,fixture_type,user_type,metric,match,num_sim_files,chuck_width,gb_depth,gb_pullback_dist,itd_id) values('"
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
		cs,cs_name,match_tool_pos,block_types,shank_sizes,default_orient,default_cs,itd_id) values('"
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

void CMFCApplication5Dlg::LoadCorrectFile(const std::string & filename, const std::string rootFile, int type)
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
		LoadITDFile(filename);
		break;
	}
}

void CMFCApplication5Dlg::LoadITDFile(const std::string & filename)
{
	std::string line;
	string com = "select id from filetable where filepath='"+ filename + "'";
	std::vector<std::vector<string>> res;
	DBOperations::ExecuteCommand(com.c_str(), &res);
	string file_id = res[0][0];
	std::ifstream infile(filename);
	ostringstream ss;
	ss << "insert into itd (description) values('";
	while (std::getline(infile, line))
	{
		if (line == "ints_begin" || line == "ints_end" || line == "doubles_begin" || line == "doubles_end" || line == "strs_begin"
			|| line == "strs_end" || line == "int_arrays_begin" || line == "int_arrays_end" || line == "double_arrays_begin"
			|| line == "double_arrays_end") continue;
		int x = 0;
		boost::replace_all(line, " ", "=");
		boost::algorithm::erase_all(line, "\"");
		if(!line.empty()) ss << line << ";";
	}
	ss << "')";
	int id = 0;
	DBOperations::ExecuteCommand(ss.str().c_str(), NULL, true, &id);
	ostringstream tmp;
	tmp << "Insert into file_object (file_id,item_id,typ_id) values(" << file_id << "," << id << ",0);";
	DBOperations::ExecuteCommand(tmp.str().c_str(), NULL);
}

void CMFCApplication5Dlg::InsertFileInDB(const std::string & filename, std::string date, const std::string rootFile, int type)
{
	string comm("INSERT INTO FILETABLE (filepath,dateofmod) VALUES ('");
	comm += filename + "','" + date + "');";
	DBOperations::ExecuteCommand(comm.c_str(), NULL);
	LoadCorrectFile(filename, rootFile, type);
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
		if (is_directory(itr->status())) {
			directories.push_back(itr->path());
			continue;
		}
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
		if (!doesExist)	InsertFileInDB(x, date, itdParent->string(), type);
		else if (isModified) UpdateFileInDB(type, id, x, date, itdParent->string());
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
	LoadCorrectFile(filename, rootFile, type);
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
	DDX_Control(pDX, IDC_LIST2, m_listResult);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication5Dlg::OnBnClickedButton1)
	ON_NOTIFY(TVN_SELCHANGED, 0x1221, &CMFCApplication5Dlg::OnTvnItemChangedTree1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication5Dlg::OnBnClickedButton2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, OnItemchangedList2)
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
		CRect(740, 10, 1095, 486), this, 0x1221);
	SetBitmap(L"init.bmp");
	m_listResult.SetExtendedStyle(LVS_EX_FULLROWSELECT |  LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_listResult.InsertColumn(0, _T("ITD"), LVCFMT_LEFT, 180);
	m_listResult.InsertColumn(1, _T("Make"), LVCFMT_LEFT, 170);
	m_listResult.InsertColumn(2, _T("Name"), LVCFMT_LEFT, 170);

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
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

//void CMFCApplication5Dlg::OnLbnSelchangeList1()
//{
//	//int i = m_Values.GetCaretIndex();
//	int i = 0;
//	CString tmp = Items[ItemsNames[i]];
//	HBITMAP startBitmap = (HBITMAP)LoadImage(NULL, tmp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//	m_PictureControl.SetBitmap(startBitmap);
//	index = 0;
//}

void CMFCApplication5Dlg::OnBnClickedButton1()
{
	DBOperations::Create("script.txt",&filesInDb);
	CFolderDialog dlg(_T("Root folder is C:\\ "), NULL, this);
	dlg.SetRootFolder(_T("C:\\input_do_ineksera"));
	//LPCTSTR m_strDisplayName;
	m_strFolderPath = L"C:\\input_do_ineksera";
	bool b = false;
	path p;
	LoadFilesBuildDB(m_strFolderPath, NULL, &b,&p);
	for (auto &x : filesInDb)
		if (!x.second) 
			DBOperations::RemoveFileFromDB(x.first);
	/*if( dlg.DoModal() == IDOK  )
	{
	m_strFolderPath = dlg.GetFolderPath();
	LoadFiles(m_strFolderPath, NULL, &b);
	}*/
}
void CMFCApplication5Dlg::OnTvnItemChangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
	wstring finalString;// = m_strFolderPath;
	HTREEITEM a = m_tree.GetSelectedItem();
	CString s = m_tree.GetItemText(a);
	finalString += LPCTSTR("\\");
	finalString += (LPCTSTR)s;
	while (a != NULL)
	{
		a = m_tree.GetParentItem(a);
		s = m_tree.GetItemText(a);
		auto tmp = finalString;
		finalString = LPCTSTR("\\") + s;
		finalString += tmp;
	}
	auto tmp = finalString;
	finalString.clear();
	finalString = CString(m_strFolderPath);
	finalString += tmp;
	SetBitmap(finalString.c_str());
}


void CMFCApplication5Dlg::OnBnClickedButton2()
{
	CString t;
	m_richEditSearch.GetWindowTextW(t);
	CT2CA tmp(t);
	std::string text(tmp);
	vector<string> keys,values;
	GetParams(&text, &keys, &values);
	if (keys.size() == 0 || (keys.size() != values.size())) return;
	ostringstream fix,tool;
	string txt = keys[0] + "=" + values[0];
	for (int i = 1; i < keys.size(); i++)
		txt += " and f." + keys[i] + "='" + values[i] + "'";
	int x = 0;
	fix << "select ft.filepath, f.make, f.name, f.file from Fixture f "
		<< "join filetable ft on f.itd_id = ft.id where f." + txt;
	tool << "select ft.filepath, f.make, f.name, f.file from Toolblock f "
		<< "join filetable ft on f.itd_id = ft.id where f." + txt;
	vector<vector<string>> result,result1;
	bool b = DBOperations::ExecuteCommand(fix.str().c_str(), &result);
	bool b1 = DBOperations::ExecuteCommand(tool.str().c_str(), &result1);
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	if (b) {
		for (int i = 0; i < result.size(); i++) {
			path p(result[i][0]);
			pathsToSearch.push_back(p.parent_path());
			wstring path = p.filename().wstring() + L":fixture";
			int nIndex = m_listResult.InsertItem(0, path.c_str());
			wstring w = converter.from_bytes(result[i][1]);
			m_listResult.SetItemText(nIndex, 1, w.c_str());
			w = converter.from_bytes(result[i][2]);
			m_listResult.SetItemText(nIndex, 2, w.c_str());
			w = converter.from_bytes(result[i][3] + ".bmp");
			resultFiles.push_back(w);
		}
	}
	if (b1) {
		for (int i = 0; i < result1.size(); i++) {
			path p(result1[i][0]);
			pathsToSearch.push_back(p.parent_path());
			wstring path = p.filename().wstring() + L":toolblock";
			int nIndex = m_listResult.InsertItem(0, path.c_str());
			wstring w = converter.from_bytes(result1[i][1]);
			m_listResult.SetItemText(nIndex, 1, w.c_str());
			w = converter.from_bytes(result1[i][2]);
			m_listResult.SetItemText(nIndex, 2, w.c_str()); 
			w = converter.from_bytes(result1[i][3] + ".bmp");
			resultFiles.push_back(w);
		}
	}
	if (!b && !b1)
		MessageBox(_T("Nothing was found"), _T("Info"), MB_ICONINFORMATION | MB_OK);
}

void CMFCApplication5Dlg::SetBitmap(const wchar_t * filePath)
{
	CImage img1;
	int dimx = 716, dimy = 476;
	img1.Load(filePath);
	if (img1 != NULL)
	{
		CDC *screenDC = GetDC();
		CDC mDC;
		mDC.CreateCompatibleDC(screenDC);
		CBitmap b;
		b.CreateCompatibleBitmap(screenDC, dimx, dimy);
		CBitmap *pob = mDC.SelectObject(&b);
		mDC.SetStretchBltMode(HALFTONE);
		img1.StretchBlt(mDC.m_hDC, 0, 0, dimx, dimy, 0, 0, img1.GetWidth(), img1.GetHeight(), SRCCOPY);
		mDC.SelectObject(pob);
		m_PictureControl.SetBitmap((HBITMAP)b.Detach());
		ReleaseDC(screenDC);
	}
}

void CMFCApplication5Dlg::GetParams(std::string *text,std::vector<string>* keys, std::vector<string>* values)
{
	if (text->size() == 0) return;
	m_listResult.DeleteAllItems();
	vector<string> lines;
	boost::replace_all(*text, ";", "\n");
	boost::erase_all(*text, "\r");
	boost::split(lines, *text, boost::is_any_of("\n"));
	for each (string line in lines)
	{
		vector<string> splittedLine, arguments,valueV;
		boost::split(splittedLine, line, boost::is_any_of("="));
		if (splittedLine.size() < 2)
		{
			MessageBox(_T("Incorrect sytax. Input key=value"), _T("Error"), MB_ICONERROR | MB_OK);
			return;
		}
		boost::split(arguments, splittedLine[0], boost::is_any_of(" "));
		string arg = "";
		bool b = false;
		for (int i = 0; i < arguments.size(); i++)
		{
			if (arguments[i].size() > 0) {
				if (!b) arg += arguments[i];
				else arg += "_" + arguments[i];
				b = true;
			}
		}
		if (arg.size() == 0 || splittedLine[1].size() == 0) continue;
		keys->push_back(arg);
		boost::replace_all(splittedLine[1], "false", "0");
		boost::replace_all(splittedLine[1], "true", "1");
		boost::split(valueV, splittedLine[1], boost::is_any_of(" "));
		string value = "'";
		b = false;
		for (int i = 0; i < valueV.size(); i++)
		{
			if (valueV[i].size() > 0)
			{
				if (!b) value += valueV[i];
				else value += " " + valueV[i];
				b = true;
			}
		}
		value += "'";
		values->push_back(value);
	}
}

HTREEITEM CMFCApplication5Dlg::FindItem(const CString& name, CTreeCtrl& tree, HTREEITEM hRoot)
{
	// check whether the current item is the searched one
	CString text = tree.GetItemText(hRoot);
	if (text.Compare(name) == 0)
		return hRoot;

	// get a handle to the first child item
	HTREEITEM hSub = tree.GetChildItem(hRoot);
	// iterate as long a new item is found
	while (hSub)
	{
		// check the children of the current item
		HTREEITEM hFound = FindItem(name, tree, hSub);
		if (hFound)
			return hFound;

		// get the next sibling of the current item
		hSub = tree.GetNextSiblingItem(hSub);
	}

	// return NULL if nothing was found
	return NULL;
}
void CMFCApplication5Dlg::OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	POSITION pos = m_listResult.GetFirstSelectedItemPosition();
	if ((pNMListView->uChanged & LVIF_STATE) && (pNMListView->uNewState & LVIS_SELECTED))
	{
		int x = GetSelectedItem(&m_listResult);
		wstring file = resultFiles[resultFiles.size() - 1 - x];
		path found;
		if(find_file(pathsToSearch[pathsToSearch.size() - 1 - x], file, found))
			SetBitmap(found.wstring().c_str());
		else
		{
			int xa = 0;
		}
	}
}
int CMFCApplication5Dlg::GetSelectedItem(CListCtrl *plctrl)
{
	POSITION pos = plctrl->GetFirstSelectedItemPosition();
	int selected = -1;
	if (pos != NULL)
	{
		while (pos)
		{
			int nItem = plctrl->GetNextSelectedItem(pos);
			selected = nItem;
		}
	}
	return selected;
}

bool CMFCApplication5Dlg::find_file(const path& dir_path, const path& file_name, path& path_found) 
{
	const recursive_directory_iterator end;
	const auto it = find_if(recursive_directory_iterator(dir_path), end, 
		[&file_name](const directory_entry& e) {
		return e.path().filename() == file_name;
	});
	if (it == end) {
		return false;
	}
	else {
		path_found = it->path();
		return true;
	}
}