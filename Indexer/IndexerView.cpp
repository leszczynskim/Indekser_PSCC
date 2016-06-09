#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "Indexer.h"
#endif

#include "IndexerDoc.h"
#include "IndexerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;


IMPLEMENT_DYNCREATE(CIndexerView, CFormView)

BEGIN_MESSAGE_MAP(CIndexerView, CFormView)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTONEXPAND, &CIndexerView::OnBnClickedButtonexpand)
	ON_BN_CLICKED(IDC_BUTTONCOLLAPSE, &CIndexerView::OnBnClickedButtoncollapse)
	ON_BN_CLICKED(IDC_BUTTONFOLDER, &CIndexerView::OnBnClickedButtonfolder)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CIndexerView::OnLvnItemchangedList1)
	ON_COMMAND(ID_VIEW_RENDER, OnRender)
	ON_BN_CLICKED(IDC_BUTTON1, &CIndexerView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO2D, &CIndexerView::OnBnClickedRadio2d)
	ON_BN_CLICKED(IDC_RADIO3D, &CIndexerView::OnBnClickedRadio3d)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CIndexerView::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_CHECK1, &CIndexerView::OnBnClickedCheck1)
END_MESSAGE_MAP()

CIndexerView::CIndexerView()
	: CFormView(IDD_INDEXER_FORM)
	, m_radioButtons(0)
	, m_radioButtonsView(0)
{
	DirectWnd = new DX11Wnd;
	GetKeysFixture(&keysFixture);
	GetKeysToolblock(&keysToolblock);
}

CIndexerView::~CIndexerView()
{
}

void CIndexerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listResult);
	DDX_Radio(pDX, IDC_RADIOOR, m_radioButtons);
	DDX_Control(pDX, IDC_PICTURE, m_PictureControl);
	DDX_Radio(pDX, IDC_RADIO3D, m_radioButtonsView);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richEditSearch);
	DDX_Control(pDX, IDC_TREE1, m_tree1);
	DDX_Control(pDX, IDC_CHECK1, m_checkBoxScaling);
}

BOOL CIndexerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CIndexerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout(FALSE);
	ResizeParentToFit(FALSE);
	DirectWnd->SubclassDlgItem(IDC_RENDER, this);
	DirectWnd->Init();
	SetBitmap(L"init");
	m_radioButtonsView = 1;
	m_radioButtons = 0;
	UpdateData(TRUE);
	m_listResult.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_listResult.InsertColumn(0, _T("ITD"), LVCFMT_LEFT, 180);
	m_listResult.InsertColumn(1, _T("Make"), LVCFMT_LEFT, 170);
	m_listResult.InsertColumn(2, _T("Name"), LVCFMT_LEFT, 170);
	m_checkBoxScaling.SetCheck(1);
}

#ifdef _DEBUG
void CIndexerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIndexerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif

CIndexerDoc* CIndexerView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIndexerDoc)));
	return (CIndexerDoc*)m_pDocument;
}

BOOL CIndexerView::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(RGB(240, 240, 240));
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);
	return FALSE;
}

void CIndexerView::ToggleTreeNode(HTREEITEM hItem, UINT nCode)
{
	HTREEITEM hChild;
	if (m_tree1.ItemHasChildren(hItem))
	{
		m_tree1.Expand(hItem, nCode);
		hChild = m_tree1.GetChildItem(hItem);
		while (hChild)
		{
			ToggleTreeNode(hChild, nCode);
			hChild = m_tree1.GetNextItem(hChild, TVGN_NEXT);
		}
	}
}

void CIndexerView::LoadFilesBuildDB(const path & dir_path, HTREEITEM *root, bool *isFound, path* itdParent)
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
			wstring s = itr->path().filename().c_str();
			boost::erase_all(s, ".bmp");
			localIsFound = true;
			*isFound = true;
			if (!root) m_tree1.InsertItem(s.c_str(), TVI_ROOT);
			else m_tree1.InsertItem(s.c_str(), *root);
		}
		else if (itr->path().extension() == ".fb2")
			Convert_fb2_to_stl(itr->path().string());
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

void CIndexerView::LoadItemsFromXml(const std::string & filename, const std::string & itdParent, std::string children, string item, int type, string(*getString)(boost::property_tree::ptree::value_type *v, string parent))
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
		<< v->second.get<int>("default_orient") << ",'" << v->second.get<string>("default_cs")
		<< "'," << itdParentId << ");";
	return ss.str();
}

void CIndexerView::LoadCorrectFile(const std::string & filename, const std::string rootFile, int type)
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

void CIndexerView::LoadITDFile(const std::string & filename)
{
	std::string line;
	string com = "select id from filetable where filepath='" + filename + "'";
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
		if (!line.empty()) ss << line << ";";
	}
	ss << "')";
	int id = 0;
	DBOperations::ExecuteCommand(ss.str().c_str(), NULL, true, &id);
	ostringstream tmp;
	tmp << "Insert into file_object (file_id,item_id,typ_id) values(" << file_id << "," << id << ",0);";
	DBOperations::ExecuteCommand(tmp.str().c_str(), NULL);
}

void CIndexerView::InsertFileInDB(const std::string & filename, std::string date, const std::string rootFile, int type)
{
	string comm("INSERT INTO FILETABLE (filepath,dateofmod) VALUES ('");
	comm += filename + "','" + date + "');";
	DBOperations::ExecuteCommand(comm.c_str(), NULL);
	LoadCorrectFile(filename, rootFile, type);
}

void CIndexerView::SearchDirectories(std::vector<path> *directories, bool *isFound, HTREEITEM *root, path* itdParent, bool *localIsFound)
{
	for (path p : *directories)
	{
		*isFound = false;
		HTREEITEM rootTmp = NULL;
		if (!root)
			rootTmp = m_tree1.InsertItem(p.filename().c_str(), TVI_ROOT);
		else
			rootTmp = m_tree1.InsertItem(p.filename().c_str(), *root);
		LoadFilesBuildDB(p, &rootTmp, isFound, itdParent);
		if (!(*isFound))
		{
			m_tree1.DeleteItem(rootTmp);
			if (*localIsFound) *isFound = true;
		}
	}
}

void CIndexerView::GetType(const path *p, bool * isFileOk, int *type, path *itdParent)
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

void CIndexerView::UpdateFileInDB(int type, string id, const std::string & filename, std::string date, const std::string rootFile)
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
	ss << "delete from " << s << " where id in( select f.id from " << s << " f join file_object fo on fo.item_id = f.id\
		join filetable ft on ft.id = fo.file_id	where ft.id = " << id << "); delete from file_object where file_id = " << id << ";"
		<< "update filetable set dateofmod = '" << date << "' where id = " << id << ";";
	DBOperations::ExecuteCommand(ss.str().c_str(), NULL);
	LoadCorrectFile(filename, rootFile, type);
}

void CIndexerView::AddResults(wstring type, vector<vector<string>> *result)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	for (int i = 0; i < result->size(); i++) {
		path p((*result)[i][0]);
		pathsToSearch.push_back(p.parent_path());
		wstring path = p.filename().wstring() + type;
		int nIndex = m_listResult.InsertItem(0, path.c_str());
		wstring w = converter.from_bytes((*result)[i][1]);
		m_listResult.SetItemText(nIndex, 1, w.c_str());
		w = converter.from_bytes((*result)[i][2]);
		m_listResult.SetItemText(nIndex, 2, w.c_str());
		w = converter.from_bytes((*result)[i][3] + ".bmp");
		resultFiles.push_back(w);
	}
}

void CIndexerView::SetBitmap(const wchar_t * filePath)
{
	CImage img1;
	wstring s(filePath);
	s += L".bmp";
	img1.Load(s.c_str());
	if (img1 != NULL)
	{
		if (m_checkBoxScaling.GetCheck())
		{
			CRect rectTree, rectRTB;
			GetDlgItem(IDC_TREE1)->GetWindowRect(&rectTree);
			ScreenToClient(&rectTree);
			GetDlgItem(IDC_RICHEDIT21)->GetWindowRect(&rectRTB);
			ScreenToClient(&rectRTB);
			int dimx = rectTree.left - 30, dimy = rectRTB.top - 39;
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
		else
		{
			HBITMAP hbitmap = img1;
			m_PictureControl.SetBitmap(hbitmap);
		}
	}
}

void CIndexerView::GetValues(std::string *text, std::vector<string>* values)
{
	std::vector<string> tmp;
	boost::erase_all(*text, "\r");
	boost::replace_all(*text, "\n", " ");
	boost::replace_all(*text, "false", "0");
	boost::replace_all(*text, "true", "1");
	boost::split(tmp, *text, boost::is_any_of(" "));

	for (int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i] == "") continue;
		string value = "LIKE LOWER('%";
		value += tmp[i];
		value += "%')";
		values->push_back(value);
	}
}

void CIndexerView::GetKeysFixture(std::vector<string> *keys)
{
	keys->push_back("make");
	keys->push_back("file");
	keys->push_back("name");
	keys->push_back("fixture_type");
	keys->push_back("user_type");
	keys->push_back("metric");
	keys->push_back("match");
	keys->push_back("num_sim_files");
	keys->push_back("chuck_width");
	keys->push_back("gb_depth");
	keys->push_back("gb_pullback_dist");
}

void CIndexerView::GetKeysToolblock(std::vector<string> *keys)
{
	keys->push_back("make");
	keys->push_back("file");
	keys->push_back("name");
	keys->push_back("metric");
	keys->push_back("offset_x");
	keys->push_back("offset_y");
	keys->push_back("offset_z");
	keys->push_back("num_orientations");
	keys->push_back("match");
	keys->push_back("num_sim_files");
	keys->push_back("tool_pos");
	keys->push_back("match_tool_pos");
	keys->push_back("block_types");
	keys->push_back("shank_sizes");
	keys->push_back("default_orient");
	keys->push_back("default_cs");
}

string CIndexerView::GetQuery(std::vector<string>* keys, std::vector<string>* values)
{
	UpdateData(TRUE);
	string txt = "";
	for (int i = 0; i < values->size(); i++)
	{
		for (int j = 0; j < keys->size(); j++)
		{
			if (i == 0 && j == 0)
				txt = "(f." + (*keys)[0] + " " + (*values)[0];
			else if (j == 0 && m_radioButtons == 1)
				txt += ") and (f." + (*keys)[j] + " " + (*values)[i];
			else
				txt += " or f." + (*keys)[j] + " " + (*values)[i];
		}
	}
	txt += ")";
	return txt;
}

HTREEITEM CIndexerView::FindItem(const CString& name, CTreeCtrl& tree, HTREEITEM hRoot)
{
	CString text = tree.GetItemText(hRoot);
	if (text.Compare(name) == 0)
		return hRoot;
	HTREEITEM hSub = tree.GetChildItem(hRoot);
	while (hSub)
	{
		HTREEITEM hFound = FindItem(name, tree, hSub);
		if (hFound)
			return hFound;
		hSub = tree.GetNextSiblingItem(hSub);
	}
	return NULL;
}

int CIndexerView::GetSelectedItem(CListCtrl *plctrl)
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

bool CIndexerView::Find_file(const path& dir_path, const path& file_name, path& path_found)
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

void CIndexerView::OnRender()
{
	UpdateData(TRUE);
	if (m_radioButtonsView == 0)
		DirectWnd->Render();
}

string CIndexerView::ToUtf8Str(const std::wstring & wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

wstring CIndexerView::toUtf8Wstr(const std::string &str)
{
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

int CIndexerView::Convert_fb2_to_stl(const std::string & path_fb2)
{
	string outFile = path_fb2;
	outFile += ".stl";
	gc_tFacetRep fb2;
	if (fb2.Read(path_fb2.c_str()))
		return -1;
	if (FileExists(outFile)) return -1;
	std::ofstream out(outFile);
	if (!out.is_open() || !out.good()) return -1;
	if (fb2.nfacets * 3 != fb2.nverts)
	{
		std::cout << L"This is a problem: fb2.nfacets * 3 != fb2.nverts" << std::endl;
		return -1;
	}
	out << fb2.nverts << std::endl;
	for (int i = 0; i < fb2.nverts; i++)
	{
		for (int j = 0; j < 3; j++)
			out << fb2.verts[3 * i + j] << " ";
		for (int j = 0; j < 3; j++)
			out << fb2.norms[3 * i + j] << " ";
		out << endl;
	}
	out << fb2.nindices << std::endl;
	out.close();
	return 0;
}

bool CIndexerView::FileExists(const std::string& filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1) return true;
	return false;
}

void CIndexerView::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	wstring finalString;
	HTREEITEM a = m_tree1.GetSelectedItem();
	CString s = m_tree1.GetItemText(a);
	finalString += LPCTSTR("\\");
	finalString += (LPCTSTR)s;
	while (a != NULL)
	{
		a = m_tree1.GetParentItem(a);
		s = m_tree1.GetItemText(a);
		auto tmp = finalString;
		finalString = LPCTSTR("\\") + s;
		finalString += tmp;
	}
	auto tmp = finalString;
	finalString.clear();
	finalString = m_strFolderPath;
	finalString += tmp;
	m_lastPath = finalString;
	if (m_radioButtonsView == 0)
		DirectWnd->SetModel(finalString.c_str());
	else
		SetBitmap(finalString.c_str());
}

void CIndexerView::OnLButtonDown(UINT nFlags, CPoint pt)
{
	DirectWnd->SendMessage(WM_LBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
}

void CIndexerView::OnLButtonUp(UINT nFlags, CPoint pt)
{
	DirectWnd->SendMessage(WM_LBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
}

void CIndexerView::OnRButtonDown(UINT nFlags, CPoint pt)
{
	DirectWnd->SendMessage(WM_RBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
}

void CIndexerView::OnRButtonUp(UINT nFlags, CPoint pt)
{
	DirectWnd->SendMessage(WM_RBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
}

void CIndexerView::OnMouseMove(UINT nFlags, CPoint pt)
{
	DirectWnd->SendMessage(WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
}

void CIndexerView::OnMButtonUp(UINT nFlags, CPoint pt)
{
	DirectWnd->SendMessage(WM_MBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
}

void CIndexerView::OnMButtonDown(UINT nFlags, CPoint pt)
{
	DirectWnd->SendMessage(WM_MBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
}

void CIndexerView::OnBnClickedCheck1()
{
	SetBitmap(m_lastPath.c_str());
}

void CIndexerView::OnBnClickedButton1()
{
	m_listResult.DeleteAllItems();
	CString t;
	m_richEditSearch.GetWindowTextW(t);
	CT2CA tmp(t);
	std::string text(tmp);
	vector<string> values;
	GetValues(&text, &values);
	pathsToSearch.clear();
	resultFiles.clear();
	ostringstream fix, tool;
	string txt;
	fix << "select ft.filepath, f.make, f.name, f.file from Fixture f "
		<< "join filetable ft on f.itd_id = ft.id where " + GetQuery(&keysFixture, &values);
	tool << "select ft.filepath, f.make, f.name, f.file from Toolblock f "
		<< "join filetable ft on f.itd_id = ft.id where " + GetQuery(&keysToolblock, &values);
	vector<vector<string>> result, result1;
	bool b = DBOperations::ExecuteCommand(fix.str().c_str(), &result);
	bool b1 = DBOperations::ExecuteCommand(tool.str().c_str(), &result1);
	if (b) AddResults(L"fixture", &result);
	if (b1)	AddResults(L"toolblock", &result1);
	if (!b && !b1 || (result.size() == 0 && result1.size() == 0))
		MessageBox(_T("Nothing was found"), _T("Info"), MB_ICONINFORMATION | MB_OK);
}

void CIndexerView::OnBnClickedRadio2d()
{
	GetDlgItem(IDC_RENDER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PICTURE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);
	SetBitmap(m_lastPath.c_str());
}

void CIndexerView::OnBnClickedRadio3d()
{
	GetDlgItem(IDC_RENDER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_PICTURE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);
	DirectWnd->SetModel(m_lastPath);
}

void CIndexerView::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	POSITION pos = m_listResult.GetFirstSelectedItemPosition();
	if ((pNMListView->uChanged & LVIF_STATE) && (pNMListView->uNewState & LVIS_SELECTED))
	{
		int x = GetSelectedItem(&m_listResult);
		wstring file = resultFiles[resultFiles.size() - 1 - x];
		path found;
		if (Find_file(pathsToSearch[pathsToSearch.size() - 1 - x], file, found))
		{
			wstring s = found.wstring();
			boost::erase_all(s, ".bmp");
			m_lastPath = s;
			if (m_radioButtonsView == 0) DirectWnd->SetModel(s.c_str());
			else SetBitmap(s.c_str());
		}
	}
}

void CIndexerView::OnBnClickedButtonfolder()
{
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = _T("Select Folder");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl == 0) return;
	m_tree1.DeleteAllItems();
	TCHAR folderPath[MAX_PATH];
	SHGetPathFromIDList(pidl, folderPath);
	IMalloc * imalloc = 0;
	if (SUCCEEDED(SHGetMalloc(&imalloc)))
	{
		imalloc->Free(pidl);
		imalloc->Release();
	}
	m_strFolderPath = folderPath;
	DBOperations::Create("script.txt", &filesInDb);
	int fileCount = 0;
	try
	{
		for (recursive_directory_iterator it(m_strFolderPath); it != recursive_directory_iterator(); ++it)
			if (it->path().extension() == ".fb2") fileCount++;
	}
	catch (exception) {
		MessageBox(_T("Wrong directory!"), _T("Error"),	MB_ICONERROR | MB_OK);
		return;
	}
	bool b = false;
	path p;
	LoadFilesBuildDB(m_strFolderPath, NULL, &b, &p);
	for (auto &x : filesInDb)
		if (!x.second) DBOperations::RemoveFileFromDB(x.first);
}

void CIndexerView::OnBnClickedButtonexpand()
{
	ToggleTreeNode(m_tree1.GetRootItem(), TVE_EXPAND);
}

void CIndexerView::OnBnClickedButtoncollapse()
{
	ToggleTreeNode(m_tree1.GetRootItem(), TVE_COLLAPSE);
}