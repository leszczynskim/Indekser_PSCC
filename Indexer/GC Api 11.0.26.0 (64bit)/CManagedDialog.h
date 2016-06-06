#ifndef _CMANAGEDDIALOG_H
#define _CMANAGEDDIALOG_H

#include <float.h>              // floating point precision
#include <math.h>
#include <vector>
#include <map>

#define	MachineAccyAPI		0.00005
#define CMD_DEG_TO_RAD		0.01745329251994329576923690768489
#define CMD_RAD_TO_DEG		57.295779513082320876798154814105

class CTrapEditCtrl
{
public:
	typedef enum
	{
		eTECShort,
		eTECDouble
	} teTECDataType;
	CTrapEditCtrl(bool doParse = false, bool bTrapKeys = true) : m_bDoParse(doParse), m_bTrapKeys(bTrapKeys), m_hTECWnd(0), m_TECprevProc(0), owned(true)
	{
		m_eDataType = eTECDouble;
		m_eLoadType = gc_eUndef_LT;
		m_eETPrecType = gc_eLinear_PT;
		m_bRadDia   = false;
		m_bPartUnitsFormat = false;
		m_bToolUnitsFormat = false;
		m_userPrecisionStringFunc = nullptr;
	}
	typedef int (*ManageHandleMapFunc)(void* handle, void* data, int flag);
	static int ManageWindowHandleMap(void* handle, void* data, int flag)
	{
		static bool initted = false;
		static ManageHandleMapFunc _manageWindowHandleMap = nullptr;
		if (!initted)
		{
			initted = true;
			_manageWindowHandleMap = reinterpret_cast<ManageHandleMapFunc>(GetProcAddress(0, "gc_ManageWindowHandleMap"));
		}
		if (_manageWindowHandleMap)
			return _manageWindowHandleMap(handle, data, flag);
		return -1;
	}
	typedef int(*GetStringPrecisionFunc)(bool bUseTool, int* iPrec);
	typedef int(*GetNETPrecisionFunc)(int eETPrecType);
	static int GetStringPrecision(bool bUsePartUnitsFormat, bool toolPrecision, gc_teETPrecType eETPrecType)
	{
		static bool initted = false;
		static GetStringPrecisionFunc _getStringPrecision = nullptr;
		static GetNETPrecisionFunc _getNetPrecision = nullptr;
		if (!initted)
		{
			initted = true;
			_getStringPrecision = reinterpret_cast<GetStringPrecisionFunc>(GetProcAddress(0, "gc_GetStringPrecision"));
			_getNetPrecision = reinterpret_cast<GetNETPrecisionFunc>(GetProcAddress(0, "gc_GetNETPrecision"));
		}
		if ((toolPrecision) || (bUsePartUnitsFormat) && (_getStringPrecision))
		{
			int iPrec = 7;
			if (!_getStringPrecision(toolPrecision, &iPrec))
				return iPrec;
		}
		if (_getNetPrecision)
		{
			return(_getNetPrecision(eETPrecType));
		}
		return 7;
	}
	typedef int(*PrecisionStringFunc)(char *s, double dVal, bool bUseCStr, int iPrec);
	static int PrecisionString(char *s, double dVal, bool bUsePartUnitsFormat, bool bUseToolUnitsFormat, gc_teETPrecType eETPrecType)
	{
		static bool initted = false;
		static PrecisionStringFunc _precisionString = nullptr;
		if (!initted)
		{
			initted = true;
			_precisionString = reinterpret_cast<PrecisionStringFunc>(GetProcAddress(0, "gc_PrecisionString"));
		}
		if (_precisionString)
		{
			int nPrecision = GetStringPrecision(bUsePartUnitsFormat, bUseToolUnitsFormat, eETPrecType);
			return _precisionString(s, dVal, true, nPrecision);
		}
		return -1;
	}
	int FormatString(char *s, double dVal, bool bUsePartUnitsFormat, bool bUseToolUnitsFormat, gc_teETPrecType eETPrecType)
	{
		if (m_userPrecisionStringFunc)
			return 	m_userPrecisionStringFunc(s, dVal, true, bUsePartUnitsFormat ? -1 : GetStringPrecision(bUsePartUnitsFormat, bUseToolUnitsFormat, eETPrecType));
		else
			return PrecisionString(s, dVal, bUsePartUnitsFormat, bUseToolUnitsFormat, eETPrecType);
	}
	virtual ~CTrapEditCtrl()
	{
		if (m_hTECWnd != 0)
		{
			if (!ManageWindowHandleMap((void*)m_hTECWnd, 0, gc_eManageWindowHandleMap_Remove))
			{
#ifdef _MEDT_UNICODE_VER
				SetWindowLongPtrW(m_hTECWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_TECprevProc));
#else
				SetWindowLongPtrA(m_hTECWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_TECprevProc));
#endif
				//				if (owned)
				//					DestroyWindow(m_hTECWnd);
				m_hTECWnd = 0;
				m_TECprevProc = 0;
			}
		}
	}
	HWND m_hTECWnd;
	WNDPROC m_TECprevProc;
	void Subclass(HWND hWnd, bool ownit = false)
	{
		if (ManageWindowHandleMap((void*)hWnd, 0, gc_eManageWindowHandleMap_Get) != 0)
		{
			owned = ownit;
			m_hTECWnd = hWnd;
			void* data = (void*)this;
			ManageWindowHandleMap((void*)hWnd, &data, gc_eManageWindowHandleMap_Add);
#ifdef _MEDT_UNICODE_VER
			m_TECprevProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WinProc)));
#else
			m_TECprevProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WinProc)));
#endif
			//SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) | ES_WANTRETURN);
		}
	}
public:
	void SetDataType(teTECDataType eDataType, gc_teETLoadType eLoadType = gc_eUndef_LT, gc_teETPrecType eETPrecType = gc_eLinear_PT, bool bRadDia = false, bool bPartUnitsFormat = false, bool bToolUnitsFormat = false)
	{ 
		m_eDataType = eDataType; 
		m_eLoadType = eLoadType;
		m_eETPrecType = eETPrecType;
		m_bRadDia = bRadDia;
		m_bPartUnitsFormat = bPartUnitsFormat;
		m_bToolUnitsFormat = bToolUnitsFormat;
	}
	teTECDataType GetDataType( void )
	{
		return m_eDataType;
	}
	gc_teETLoadType GetLoadType( void )
	{
		return m_eLoadType;
	}
	gc_teETPrecType GetPrecisionType(void)
	{
		return m_eETPrecType;
	}
	bool GetRadDia(void)
	{
		return m_bRadDia;
	}
	bool GetPartUnitsFormat( void )
	{
		return m_bPartUnitsFormat;
	}
	bool GetToolUnitsFormat(void)
	{
		return m_bToolUnitsFormat;
	}
	void SetPrecisionStringFunc(PrecisionStringFunc func)
	{
		m_userPrecisionStringFunc = func;
	}
	PrecisionStringFunc GetPrecisionStringFunc()
	{
		return m_userPrecisionStringFunc;
	}
	static void SetForceEval(bool bSet)
	{
		AccessForceEval(&bSet);
	}
	void EvalText( char* str = nullptr )
	{
		char	s[256];
		char	saveS[256];
		double	dVal;
		if (str)
			strcpy_s(s, str);
		else
			GetWindowTextA(m_hTECWnd, s, 64 );
		strcpy_s(saveS, sizeof(saveS), s);
		if( Parse( s, &dVal, ( m_eDataType == eTECShort ) ) )
		{
			if (strcmp(s, saveS))
			{
				::SetWindowTextA(m_hTECWnd, s );
				short iLen = (short)strlen(s);
#ifdef _MEDT_UNICODE_VER
				SendMessageW(m_hTECWnd, EM_SETSEL, iLen, iLen);
#else
				SendMessageA(m_hTECWnd, EM_SETSEL, iLen, iLen);
#endif
			}
		}
	}
protected:
	static bool AccessForceEval(const bool* bSet = 0)
	{
		static bool bForceEval = false;
		if (bSet)
			bForceEval = *bSet;
		return bForceEval;
	}
	static int GetConsumeKeyMessage()
	{
		static int g_consumekeyMsg = RegisterWindowMessageA("VIRTM_CONSUMEKEY");
		return g_consumekeyMsg;
	}
	bool Convertor(int key)
	{
		switch (key)
		{
		case 'm':	// in -> mm
		case 'M':	// in -> mm
		case 'i':	// mm - > in
		case 'I':	// mm - > in
		case 'r':	// square root
		case 'R':	// square root
		case 's':	// sin
		case 'S':	// sin
		case 'c':	// cos
		case 'C':	// cos
		case 't':	// tangent
		case 'T':	// tangent
		case 'a':	// arctangent
		case 'A':	// arctangent
			return true;
		}
		return false;
	}
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if ((m_bTrapKeys) && (message == GetConsumeKeyMessage()))
		{
			if (IncludeConsumeKey((int)wParam))
			{
#ifdef _MEDT_UNICODE_VER
				(m_TECprevProc) ? CallWindowProcW(m_TECprevProc, m_hTECWnd, message, wParam, lParam) : DefWindowProcW(m_hTECWnd, message, wParam, lParam);
#else
				(m_TECprevProc) ? CallWindowProcA(m_TECprevProc, m_hTECWnd, message, wParam, lParam) : DefWindowProcA(m_hTECWnd, message, wParam, lParam);
#endif
				return TRUE;
			}
		}
		else if (message == WM_NCDESTROY)
		{
#ifdef _MEDT_UNICODE_VER
			LRESULT lr = CallWindowProcW(m_TECprevProc, m_hTECWnd, message, wParam, lParam);
#else
			LRESULT lr = CallWindowProcA(m_TECprevProc, m_hTECWnd, message, wParam, lParam);
#endif
			//if (owned)
			//	delete this;
			//else
			{
				ManageWindowHandleMap((void*)m_hTECWnd, 0, gc_eManageWindowHandleMap_Remove);
#ifdef _MEDT_UNICODE_VER
				SetWindowLongPtrW(m_hTECWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_TECprevProc));
#else
				SetWindowLongPtrA(m_hTECWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_TECprevProc));
#endif
				m_hTECWnd = 0;
				m_TECprevProc = 0;
			}
			return lr; 
		}
		else if (m_bDoParse)
		{
			static int iQTELMsg = RegisterWindowMessageA("VIRTM_QUERYTEXTEDITLOAD");
			LRESULT lr;
			if (message == iQTELMsg && (m_eLoadType != gc_eUndef_LT))
			{
				int* iArr = (int*)lParam;
				if (wParam > 0)
					iArr[0] = (int)m_eLoadType;
				if (wParam > 1)
				{
					iArr[1] = m_bRadDia ? 1 : 0;
					if (wParam > 2)
					{
						iArr[2] = m_eETPrecType;
					}
				}
				return true;
			}
			switch(message)
			{
			case WM_LBUTTONDBLCLK:
				SendMessage(m_hTECWnd, EM_SETSEL, 0, -1 );
				return 1L;
			case WM_CHAR:
				if (wParam == VK_RETURN)
					return FALSE; //don't beep
				if (wParam == ',')
					wParam = '.';
#ifdef _MEDT_UNICODE_VER
				lr = (m_TECprevProc) ? CallWindowProcW(m_TECprevProc, m_hTECWnd, message, wParam, lParam) : DefWindowProcW(m_hTECWnd, message, wParam, lParam);
#else
				lr = (m_TECprevProc) ? CallWindowProcA(m_TECprevProc, m_hTECWnd, message, wParam, lParam) : DefWindowProcA(m_hTECWnd, message, wParam, lParam);
#endif
				EvalText();
				return lr;
			case WM_KEYDOWN:
				if (wParam == VK_RETURN)
				{
					SetForceEval(true);
					EvalText();
					SetForceEval(false);
					return FALSE; //don't beep
				}
				else
				{
					HKL kbLayout = GetKeyboardLayout(0);
					BYTE kbState[256] = { 0 };
					GetKeyboardState(kbState);
					WORD result[16] = { 0 };
					UINT uScanCode = (UINT)MapVirtualKeyEx((UINT)wParam, 0, kbLayout);
					int rc = ToAsciiEx((UINT)wParam, uScanCode, kbState, result, 0, kbLayout);
					if ((rc > 0) && Convertor(static_cast<int>(result[0])))
					{
						//append the convertor operator to the end of the text string so that EvalText can use it when parsing.
						char s[256] = { 0 };
						char op[2] = { (char)wParam, 0 };
						GetWindowTextA(m_hTECWnd, s, 64);
						strcat_s(s, op);
						SetForceEval(true);
						EvalText(s);
						SetForceEval(false);
						return FALSE; //don't beep
					}
				}
				break;
			case WM_KILLFOCUS:
				SetForceEval( true );
				EvalText();
				SetForceEval( false );
				break;
			}
			if ((message == GetConsumeKeyMessage()) && (wParam == VK_RETURN))
			{
				SetForceEval( true );
				EvalText();
				SetForceEval( false );
			}
		}
#ifdef _MEDT_UNICODE_VER
		return (m_TECprevProc) ? CallWindowProcW(m_TECprevProc, m_hTECWnd, message, wParam, lParam) : DefWindowProcW(m_hTECWnd, message, wParam, lParam);
#else
		return (m_TECprevProc) ? CallWindowProcA(m_TECprevProc, m_hTECWnd, message, wParam, lParam) : DefWindowProcA(m_hTECWnd, message, wParam, lParam);
#endif
	}
	bool IncludeConsumeKey(int iVKey)
	{
		if (iVKey >= VK_LWIN)
			return false;
		return true;
	}
	double GetTerm(char *s1, char **s2)
	{
		double dVal;

		if ((s1[0] == 'p') || (s1[0] == 'P'))
		{
			dVal = 3.141592653589793238;
			s1++;
			strtod(s1, s2);
		}
		else
			dVal = strtod(s1, s2);

		return dVal;

	}
	BOOL Parse( char *eqn_str, double *pdValue, BOOL bTrunc )
	{
		BOOL	bEval = false;
		BOOL	bConvert = false;
		BOOL	bAddLastChar = true;
		BOOL	bEvalComma = false;
		char	sOrigStr[256];
		int		iLen;
		char	cLastChar;

		strcpy( sOrigStr, eqn_str );
		iLen = (int)strlen( eqn_str );
		if (iLen == 0)
		{
			strcpy(eqn_str, "0");
			iLen = (int)strlen( eqn_str );
		}
		cLastChar = eqn_str[iLen-1];

		if( AccessForceEval() )
		{
			bEval = true;
			bAddLastChar = false;
		}
		else
			switch( cLastChar )
		{
			case '=':
			case '+':
			case '-':
			case '*':
			case 'x':
			case 'X':
			case '/':
				bEval = true;
				eqn_str[iLen-1] = '\0';
				bAddLastChar = cLastChar != '=';
				break;
			case 'm':	// in -> mm
			case 'M':	// in -> mm
			case 'i':	// mm - > in
			case 'I':	// mm - > in
			case 'r':	// square root
			case 'R':	// square root
			case 's':	// sin
			case 'S':	// sin
			case 'c':	// cos
			case 'C':	// cos
			case 't':	// tangent
			case 'T':	// tangent
			case 'a':	// arctangent
			case 'A':	// arctangent
				bConvert = true;
				eqn_str[iLen-1] = '\0';
				break;
			case ',':
				bConvert = true;
				break;
		}

		if( bConvert )
		{
			double	dTerm1 = strtod( eqn_str, NULL );

			switch( cLastChar )
			{
			case 'm':	// in -> mm
			case 'M':	// in -> mm
				*pdValue = dTerm1 * 25.4;
				break;
			case 'i':	// mm - > in
			case 'I':	// mm - > in
				*pdValue = dTerm1 / 25.4;
				break;
			case 'r':	// square root
			case 'R':	// square root
				if( dTerm1 < 0 )
					*pdValue = dTerm1;
				else
					*pdValue = sqrt( dTerm1 );
				break;
			case 's':	// sin
			case 'S':	// sin
				*pdValue = sin( dTerm1 * CMD_DEG_TO_RAD );
				break;
			case 'c':	// cos
			case 'C':	// cos
				*pdValue = cos( dTerm1 * CMD_DEG_TO_RAD );
				break;
			case 't':	// tangent
			case 'T':	// tangent
				*pdValue = tan( dTerm1 * CMD_DEG_TO_RAD );
				break;
			case 'a':	// arctangent
			case 'A':	// arctangent
				*pdValue = atan( dTerm1 ) * CMD_RAD_TO_DEG;
				break;
			case ',':
				eqn_str[iLen-1] = '.';
				eqn_str[iLen] = '\0';
				bEvalComma = true;
				break;

			}

			// Now put new string in text box
			if( bTrunc )
			{
				int	iTrunc;

				iTrunc = (int)*pdValue;
				*pdValue = (double)iTrunc;
			}
			if( bEvalComma )
				sprintf( (char*)eqn_str, "%s", eqn_str );
			else
				FormatString(eqn_str, *pdValue, m_bPartUnitsFormat, m_bToolUnitsFormat, m_eETPrecType);

			return true;
		}
		else
		{
			if( bEval )
			{
				double	dTerm1, dTerm2;
				char	cSign;
				char	*eqn_str0;
				char	*eqn_str1;

				// Evaluate equation
				dTerm1 = GetTerm(eqn_str, &eqn_str0);

				if( strlen(eqn_str0) == 0 )
				{
					if( AccessForceEval() )
					{
						*pdValue = dTerm1;
						FormatString(eqn_str, *pdValue, m_bPartUnitsFormat, m_bToolUnitsFormat, m_eETPrecType);

					}
					else if( cLastChar != '=' )
						return false;
					else
					{
						*pdValue = dTerm1;
						FormatString(eqn_str, *pdValue, m_bPartUnitsFormat, m_bToolUnitsFormat, m_eETPrecType);
						return true;
					}
				}

				cSign = *eqn_str0++;

				dTerm2 = GetTerm(eqn_str0, &eqn_str1);

				if (eqn_str1 == eqn_str0)
				{
					if( cLastChar == '=' || AccessForceEval() )
					{
						*pdValue = dTerm1;
						FormatString(eqn_str, *pdValue, m_bPartUnitsFormat, m_bToolUnitsFormat, m_eETPrecType);
						return true;
					}
					else
						return false;
				}

				switch( cSign )
				{
				case '+':
					*pdValue = dTerm1 + dTerm2;
					break;
				case '-':
					*pdValue = dTerm1 - dTerm2;
					break;
				case '*':
				case 'x':
				case 'X':
					*pdValue = dTerm1 * dTerm2;
					break;
				case '/':
					if( dTerm2 > MachineAccyAPI )
						*pdValue = dTerm1 / dTerm2;
					else
						*pdValue = dTerm1;
					break;
				}

				if( bTrunc )
				{
					int	iTrunc;

					iTrunc = (int)*pdValue;
					*pdValue = (double)iTrunc;
				}
				FormatString(eqn_str, *pdValue, m_bPartUnitsFormat, m_bToolUnitsFormat, m_eETPrecType);
				if( bAddLastChar )
				{
					char	s[2];

					s[0] = cLastChar;
					s[1] = '\0';
					strcat( eqn_str, s );
				}
				return true;
			}
		}
		return false;
	}
	bool m_bTrapKeys;
	bool m_bDoParse;
	teTECDataType	m_eDataType;
	gc_teETLoadType m_eLoadType;
	gc_teETPrecType m_eETPrecType;
	bool            m_bRadDia;
	bool            m_bPartUnitsFormat;
	bool            m_bToolUnitsFormat;
	PrecisionStringFunc m_userPrecisionStringFunc;
private:
	bool owned;
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		void* data = 0;
		if ((ManageWindowHandleMap((void*)hWnd, &data, gc_eManageWindowHandleMap_Get) == 0) && data)
		{
			CTrapEditCtrl* wnd = (CTrapEditCtrl*)data;
			return wnd->WindowProc(message, wParam, lParam);
		}
#ifdef _MEDT_UNICODE_VER
		return DefWindowProcW(hWnd, message, wParam, lParam);
#else
		return DefWindowProcA(hWnd, message, wParam, lParam);
#endif
	}
};

#ifdef _MFC_VER
class CManagedEditCtrl : public CWnd//, public CTrapEditCtrl
{
public:
	typedef enum
	{
		eShort,
		eDouble,
		eInt
	} teDataType;
	CManagedEditCtrl()
	{
		pCtrl = new CTrapEditCtrl(true, true);
	}
	virtual void PreSubclassWindow()
	{
		pCtrl->Subclass(GetSafeHwnd(), false);
		//		ctrl.SubclassWindow(GetSafeHwnd());
		CWnd::PreSubclassWindow();
	}
	virtual ~CManagedEditCtrl()
	{
		Detach(); //control's native lifecycle is managed by pCtrl so break the link
		delete pCtrl;
	}
	void SetDataType( teDataType eDataType, gc_teETLoadType eLoadType = gc_eUndef_LT, gc_teETPrecType eETPrecType = gc_eLinear_PT, bool bRadDia = false, bool bPartUnitsFormat = false, bool bToolUnitsFormat = false)
	{ 
		pCtrl->SetDataType((CTrapEditCtrl::teTECDataType)eDataType, eLoadType, eETPrecType, bRadDia, bPartUnitsFormat, bToolUnitsFormat);
	}
	teDataType GetDataType( void )
	{
		return (teDataType)pCtrl->GetDataType();
	}
	gc_teETLoadType GetLoadType( void )
	{
		return pCtrl->GetLoadType();
	}
	gc_teETPrecType GetPrecType( void )
	{
		return pCtrl->GetPrecisionType();
	}
	bool GetRadDia( void )
	{
		return pCtrl->GetRadDia();
	}
	bool GetPartUnitsFormat( void )
	{
		return pCtrl->GetPartUnitsFormat();
	}
	bool GetToolUnitsFormat( void )
	{
		return pCtrl->GetToolUnitsFormat();
	}
	CTrapEditCtrl* Ctrl() {	return pCtrl; }
private:
	CTrapEditCtrl* pCtrl;
};


class CTrapKeys
{
public:
	void SubClassEdits(CWnd* parent, bool bTrapKeys = true)
	{
		if (!bTrapKeys)
			return;
		CString cname;
		for (CWnd* cw = parent->GetWindow(GW_CHILD); cw; cw = cw->GetWindow(GW_HWNDNEXT))
		{
			GetClassName(cw->GetSafeHwnd(), cname.GetBuffer(256), 256);
			cname.ReleaseBuffer();
			if ((!cname.CompareNoCase(_T("EDIT"))) && 
				(CTrapEditCtrl::ManageWindowHandleMap((void*)cw->GetSafeHwnd(), 0, gc_eManageWindowHandleMap_Get) != 0))
			{ // if Edit and not already subclassed
				CTrapEditCtrl* ctl = new CTrapEditCtrl(false, bTrapKeys);
				ctl->Subclass(cw->GetSafeHwnd(), false);
				m_editCtrl.push_back(ctl);
			}
		}
	}
	virtual ~CTrapKeys()
	{
		for (int i=0; i < (int)m_editCtrl.size(); i++)
			delete m_editCtrl[i];
	}
	std::vector<CTrapEditCtrl*> m_editCtrl;
};



//
// Context help mapping helper class
// Context help maps can be created as arrays of BalloonHelpMap type
// e.g.:
//	ContextHelpMap chmap[] = {
//		//ID			contextID
//		{IDC_X,			1},
//		{IDC_Y,			2},
//		{IDOK,			3},
//		{IDCANCEL,		4}
//	};
// And then passed to the ProcessMap method to assign mapped context id from 
// and input control ID
// e.g.
//  ContextHelpMap::ProcessMap(id, chmap, sizeof(chmap)/sizeof(ContextHelpMap), iContextID);
//
struct ContextHelpMap
{
	int ctlID, ctextID;
	static void ProcessMap(int iID, ContextHelpMap* map, int nCount, int *ictextID)
	{
		for (int i=0; i < nCount; i++)
			if (map[i].ctlID == iID)
			{
				if (ictextID)
					*ictextID = map[i].ctextID;
			}
	}
};


//
// Balloon help mapping helper class
// Balloon help maps can be created as arrays of BalloonHelpMap type
// e.g.:
//	BalloonHelpMap bhmap[] = {
//		//ID			subID		StringID		String sub-index	Balloon tail direction
//		{IDC_X,			-1,			IDS_X,			-1,					5},
//		{IDC_Y,			-1,			IDS_Y,			-1,					5},
//		{IDOK,			-1,			IDS_OK,			-1,					5},
//		{IDCANCEL,		-1,			IDS_CANCEL,		 1,					5}
//	};
// And then passed to the ProcessMap method to assign mapped strings/positions from 
// and input control ID/subID
// e.g.
//  BalloonHelpMap::ProcessMap(id, subid, bhmap, sizeof(bhmap)/sizeof(BalloonHelpMap), sBalloonHelp, iPos);
//
struct BalloonHelpMap
{
	int ctlID, ctrlSubID, strID, strIndex, iPos;
	static void ProcessMap(int iID, int iSubID, BalloonHelpMap* map, int nCount, char* sText, int *iiPos)
	{
		for (int i=0; i < nCount; i++)
			if ((map[i].ctlID == iID) && ((map[i].ctrlSubID == iSubID) || (map[i].ctrlSubID == -1)))
			{
				CStringA s;
				s.LoadString(map[i].strID);
				if (iiPos)
					*iiPos = map[i].iPos;
				if (s.GetLength())
				{
					if (map[i].strIndex == -1)
						strncpy(sText, (LPCSTR)s, 255);
					else
					{
						char* ws = (char*)s.GetBuffer(256);
						int j = 0;

						for (char *p = strtok(ws, "|"); p && (j <= map[i].strIndex); j++, p = strtok(0, "|"))
							if (j==map[i].strIndex)
							{
								strncpy(sText, p, 255);
								break;
							}
							s.ReleaseBuffer( );
					}
				}
			}
	}
};

//
// CTransparentPictureCtrl class:
// Tranparent Picture Control class handles the transparent paints and bitmap stretching of
// the standard Win32 static BITMAP control.
//

#ifdef SUPPORTPNG
#include <ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

class CGdiplusResBitmap
{
protected:
	HGLOBAL m_hBuffer;

public:
	Gdiplus::Bitmap* m_pBitmap;
	operator Gdiplus::Bitmap*() const	{ return m_pBitmap; }
	CGdiplusResBitmap()					{ m_pBitmap = NULL; m_hBuffer = NULL; }
	CGdiplusResBitmap(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL)
	{
		m_pBitmap = NULL; m_hBuffer = NULL; Load(id, pType, hInst);
	}
	virtual ~CGdiplusResBitmap()			{ Empty(); }

	void Empty()
	{
		if (m_pBitmap)
			delete m_pBitmap;
		m_pBitmap = NULL;
		if (m_hBuffer)
		{
			::GlobalUnlock(m_hBuffer);
			::GlobalFree(m_hBuffer);
			m_hBuffer = NULL;
		}
	}

	bool LoadFromFile(LPCWSTR pFile)
	{
		Empty();
		m_pBitmap = Gdiplus::Bitmap::FromFile(pFile);
		return m_pBitmap->GetLastStatus() == Gdiplus::Ok;
	}

	bool Load(LPCTSTR pName, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL)
	{
		Empty();

		HRSRC hResource = ::FindResource(hInst, pName, pType);
		if (!hResource)
			return false;

		DWORD imageSize = ::SizeofResource(hInst, hResource);
		if (!imageSize)
			return false;

		const void* pResourceData = ::LockResource(::LoadResource(hInst, hResource));
		if (!pResourceData)
			return false;

		m_hBuffer = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
		if (m_hBuffer)
		{
			void* pBuffer = ::GlobalLock(m_hBuffer);
			if (pBuffer)
			{
				CopyMemory(pBuffer, pResourceData, imageSize);

				IStream* pStream = NULL;
				if (::CreateStreamOnHGlobal(m_hBuffer, FALSE, &pStream) == S_OK)
				{
					m_pBitmap = Gdiplus::Bitmap::FromStream(pStream);
					pStream->Release();
					if (m_pBitmap)
					{
						if (m_pBitmap->GetLastStatus() == Gdiplus::Ok)
							return true;

						delete m_pBitmap;
						m_pBitmap = NULL;
					}
				}
				::GlobalUnlock(m_hBuffer);
			}
			::GlobalFree(m_hBuffer);
			m_hBuffer = NULL;
		}
		return false;
	}

	bool Load(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL)
	{
		return Load(MAKEINTRESOURCE(id), pType, hInst);
	}
};
#endif

class CTransparentPictureCtrl : public CWnd
{
protected:
#ifdef SUPPORTPNG
	CGdiplusResBitmap m_pngBitmap;
#endif
	ULONG_PTR         m_gdiplusToken;
public:
	CTransparentPictureCtrl() : m_transRGB(RGB(255, 0, 255)), m_gdiplusToken(0)
	{
	}
	virtual ~CTransparentPictureCtrl()
	{
#ifdef SUPPORTPNG
		m_pngBitmap.Empty();
		if (m_gdiplusToken)
			Gdiplus::GdiplusShutdown(m_gdiplusToken);
#endif
	}
	void SetPNGBitmap(const int resourceID)
	{
#ifdef SUPPORTPNG
		if (!m_gdiplusToken)
		{
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
		}
		m_pngBitmap.Load(resourceID, _T("PNG"), AfxGetResourceHandle());
		if (GetSafeHwnd())
			Invalidate();
#endif
	}
	inline void SetTransparentColor(COLORREF transRGB) { m_transRGB = transRGB; }
	static void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, int xStart, int yStart,
		int nWidth, int nHeight, COLORREF cTransparentColor)
	{
		COLORREF crOldBack = SetBkColor(hdc, 0x00FFFFFF);
		COLORREF crOldText = SetTextColor(hdc, 0x00000000);
		HDC dcImage, dcTrans;
		HBITMAP bitmapTrans, pOldBitmapImage, pOldBitmapTrans;
		BITMAP  bm;
		int bmpWidth, bmpHeight;
		// Create two memory dcs for the image and the mask
		dcImage = CreateCompatibleDC(hdc);
		dcTrans = CreateCompatibleDC(hdc);
		// Select the image into the appropriate dc
		pOldBitmapImage = (HBITMAP)SelectObject(dcImage, hBitmap);
		// Create the mask bitmap
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
		bmpWidth = bm.bmWidth;
		bmpHeight = bm.bmHeight;
		bitmapTrans = CreateBitmap(bmpWidth, bmpHeight, 1, 1, NULL);
		// Select the mask bitmap into the appropriate dc
		pOldBitmapTrans = (HBITMAP)SelectObject(dcTrans, bitmapTrans);
		// Build mask based on transparent colour
		SetBkColor(dcImage, cTransparentColor);
		BitBlt(dcTrans, 0, 0, bmpWidth, bmpHeight, dcImage, 0, 0, SRCCOPY);
		// Do the work - True Mask method - cool if not actual display
		HDC dcTemp = CreateCompatibleDC(hdc);
		HBITMAP hBitmapTemp = CreateCompatibleBitmap(hdc, nWidth, nHeight);
		HBITMAP	hOldTempBitmapImage = (HBITMAP)SelectObject(dcTemp, hBitmapTemp);
		BitBlt(dcTemp, 0, 0, nWidth, nHeight, hdc,  xStart, yStart, SRCCOPY);
		StretchBlt(dcTemp, 0, 0, nWidth, nHeight, dcImage, 0, 0, bmpWidth, bmpHeight, SRCINVERT);
		StretchBlt(dcTemp, 0, 0, nWidth, nHeight, dcTrans, 0, 0, bmpWidth, bmpHeight, SRCAND);
		StretchBlt(dcTemp, 0, 0, nWidth, nHeight, dcImage, 0, 0, bmpWidth, bmpHeight, SRCINVERT);
		BitBlt(hdc, xStart, yStart, nWidth, nHeight, dcTemp, 0, 0, SRCCOPY);
		DeleteObject(SelectObject(dcTemp, hOldTempBitmapImage));
		DeleteDC(dcTemp);
		// Restore settings
		SelectObject(dcImage, pOldBitmapImage);
		SelectObject(dcTrans, pOldBitmapTrans);
		SetBkColor(hdc, crOldBack);
		SetTextColor(hdc, crOldText);
		DeleteObject(bitmapTrans);
		DeleteDC(dcImage);
		DeleteDC(dcTrans);
	}
protected:
	COLORREF m_transRGB;

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
		case WM_ERASEBKGND:
			{
				HDC  hDC = (HDC)wParam;
				CDC dc;
				dc.Attach(hDC);
				CRect r;
				GetClientRect(&r);
#ifdef SUPPORTPNG
				if(m_pngBitmap.m_pBitmap)
					dc.FillSolidRect(&r, GetSysColor(COLOR_BTNFACE));
				else
#endif
				{
					dc.SelectObject(GetSysColorBrush(COLOR_BTNFACE));
					dc.PatBlt(r.left, r.top, r.right-r.left, r.bottom-r.top, SRCCOPY);
				}
				dc.Detach();
			}
			return TRUE;
		case WM_PAINT:
#ifdef SUPPORTPNG
			if (m_pngBitmap.m_pBitmap)
			{
				CPaintDC dc(this);
				CRect r;
				GetClientRect(&r);
				if (((GetStyle() & SS_REALSIZEIMAGE) != SS_REALSIZEIMAGE) && (m_pngBitmap.m_pBitmap->GetWidth() != r.Width() || m_pngBitmap.m_pBitmap->GetHeight() != r.Height()))
				{
					Gdiplus::Graphics(dc.GetSafeHdc()).DrawImage(m_pngBitmap, Gdiplus::RectF(Gdiplus::REAL(r.left), Gdiplus::REAL(r.top), Gdiplus::REAL(r.Width()), Gdiplus::REAL(r.Height())));
				}
				else
				{
					CPoint pt = r.TopLeft();
					if ((GetStyle() & SS_CENTERIMAGE) == SS_CENTERIMAGE)
					{
						pt.x = r.CenterPoint().x - m_pngBitmap.m_pBitmap->GetWidth() / 2;
						pt.y = r.CenterPoint().y - m_pngBitmap.m_pBitmap->GetHeight() / 2;
					}
					Gdiplus::Graphics(dc.GetSafeHdc()).DrawImage(m_pngBitmap, Gdiplus::RectF(Gdiplus::REAL(pt.x), Gdiplus::REAL(pt.y), Gdiplus::REAL(m_pngBitmap.m_pBitmap->GetWidth()), Gdiplus::REAL(m_pngBitmap.m_pBitmap->GetHeight())));
				}
				return TRUE;
			}
			else
#endif
			{
				CPaintDC dc(this);
				HBITMAP hBMP = (HBITMAP)SendMessage(STM_GETIMAGE, (WPARAM)IMAGE_BITMAP, 0);
				if (hBMP)
				{
					CRect r;
					BITMAP bi = {0};
					GetClientRect(&r);
					GetObject(hBMP, sizeof(BITMAP), &bi);
					if (((GetStyle() & SS_REALSIZEIMAGE) != SS_REALSIZEIMAGE) && (bi.bmWidth != r.Width() || bi.bmHeight != r.Height()))
					{
						CDC dcStretchImage;
						CDC dcBaseImage;
						dcStretchImage.CreateCompatibleDC(&dc);
						dcBaseImage.CreateCompatibleDC(&dc);
						CBitmap stretchBmp;
						stretchBmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
						CBitmap* osbmp = dcStretchImage.SelectObject(&stretchBmp);
						CBitmap* obbmp = dcBaseImage.SelectObject(CBitmap::FromHandle(hBMP));
						dcStretchImage.StretchBlt(0, 0, r.Width(), r.Height(), &dcBaseImage, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
						dcBaseImage.SelectObject(obbmp);
						dcStretchImage.SelectObject(osbmp);
						DrawTransparentBitmap(dc.GetSafeHdc(), (HBITMAP)stretchBmp.GetSafeHandle(), 0, 0,
							r.Width(), r.Height(), m_transRGB);
					}
					else
					{
						CPoint pt = r.TopLeft();
						if ((GetStyle() & SS_CENTERIMAGE) == SS_CENTERIMAGE)
						{
							pt.x = r.CenterPoint().x - bi.bmWidth/2;
							pt.y = r.CenterPoint().y - bi.bmHeight/2;
						}
						DrawTransparentBitmap(dc.GetSafeHdc(), hBMP, pt.x, pt.y, bi.bmWidth, bi.bmHeight, m_transRGB);
					}
				}
				return TRUE;
			}
			break;
		}
		return CWnd::WindowProc(message, wParam, lParam);
	}
};

//should only be used for the clearance diagram for processes that implement mill feature depth
class CMFTransparentPictCtrl : public CWnd
{
public:
	CMFTransparentPictCtrl() : m_transRGB(RGB(242, 8, 132)), m_frameRGB(RGB(255, 0, 0)) { }
	virtual ~CMFTransparentPictCtrl() {	}
	inline void SetTransparentColor(COLORREF transRGB) { m_transRGB = transRGB; }
	void SetBitmap(int nID)
	{
		if (m_bitmap.GetSafeHandle())
			m_bitmap.DeleteObject();
		m_bitmap.Attach(LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(nID)));
		if (GetSafeHwnd() && IsWindowVisible())
			Invalidate();
	}

	static void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, int xStart, int yStart,
		int nWidth, int nHeight, COLORREF cTransparentColor)
	{
		COLORREF crOldBack = SetBkColor(hdc, 0x00FFFFFF);
		COLORREF crOldText = SetTextColor(hdc, 0x00000000);
		HDC dcImage, dcTrans;
		HBITMAP bitmapTrans, pOldBitmapImage, pOldBitmapTrans;
		BITMAP  bm;
		int bmpWidth, bmpHeight;
		// Create two memory dcs for the image and the mask
		dcImage = CreateCompatibleDC(hdc);
		dcTrans = CreateCompatibleDC(hdc);
		// Select the image into the appropriate dc
		pOldBitmapImage = (HBITMAP)SelectObject(dcImage, hBitmap);
		// Create the mask bitmap
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
		bmpWidth = bm.bmWidth;
		bmpHeight = bm.bmHeight;
		bitmapTrans = CreateBitmap(bmpWidth, bmpHeight, 1, 1, NULL);
		// Select the mask bitmap into the appropriate dc
		pOldBitmapTrans = (HBITMAP)SelectObject(dcTrans, bitmapTrans);
		// Build mask based on transparent colour
		SetBkColor(dcImage, cTransparentColor);
		BitBlt(dcTrans, 0, 0, bmpWidth, bmpHeight, dcImage, 0, 0, SRCCOPY);
		// Do the work - True Mask method - cool if not actual display
		HDC dcTemp = CreateCompatibleDC(hdc);
		HBITMAP hBitmapTemp = CreateCompatibleBitmap(hdc, nWidth, nHeight);
		HBITMAP	hOldTempBitmapImage = (HBITMAP)SelectObject(dcTemp, hBitmapTemp);
		BitBlt(dcTemp, 0, 0, nWidth, nHeight, hdc,  xStart, yStart, SRCCOPY);
		StretchBlt(dcTemp, 0, 0, nWidth, nHeight, dcImage, 0, 0, bmpWidth, bmpHeight, SRCINVERT);
		StretchBlt(dcTemp, 0, 0, nWidth, nHeight, dcTrans, 0, 0, bmpWidth, bmpHeight, SRCAND);
		StretchBlt(dcTemp, 0, 0, nWidth, nHeight, dcImage, 0, 0, bmpWidth, bmpHeight, SRCINVERT);
		BitBlt(hdc, xStart, yStart, nWidth, nHeight, dcTemp, 0, 0, SRCCOPY);
		DeleteObject(SelectObject(dcTemp, hOldTempBitmapImage));
		DeleteDC(dcTemp);
		// Restore settings
		SelectObject(dcImage, pOldBitmapImage);
		SelectObject(dcTrans, pOldBitmapTrans);
		SetBkColor(hdc, crOldBack);
		SetTextColor(hdc, crOldText);
		DeleteObject(bitmapTrans);
		DeleteDC(dcImage);
		DeleteDC(dcTrans);
	}
protected:
	COLORREF m_transRGB;
	COLORREF m_frameRGB;
	CBitmap  m_bitmap;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
		case WM_ERASEBKGND:
			{
				HDC  hDC = (HDC)wParam;
				RECT r;
				GetClientRect(&r);
				SelectObject(hDC, GetSysColorBrush(COLOR_BTNFACE));
				PatBlt(hDC, r.left, r.top, r.right-r.left, r.bottom-r.top, SRCCOPY);
			}
			return TRUE;
		case WM_PAINT:
			{
				CPaintDC dc(this);
				CRect r;
				GetClientRect(&r);
				HBITMAP hBMP = (HBITMAP)m_bitmap.GetSafeHandle();
				if (hBMP)
				{
					BITMAP bi = {0};
					GetObject(hBMP, sizeof(BITMAP), &bi);
					if (((GetStyle() & SS_REALSIZEIMAGE) != SS_REALSIZEIMAGE) && (bi.bmWidth != r.Width() || bi.bmHeight != r.Height()))
					{
						CDC dcStretchImage;
						CDC dcBaseImage;
						dcStretchImage.CreateCompatibleDC(&dc);
						dcBaseImage.CreateCompatibleDC(&dc);
						CBitmap stretchBmp;
						stretchBmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
						CBitmap* osbmp = dcStretchImage.SelectObject(&stretchBmp);
						CBitmap* obbmp = dcBaseImage.SelectObject(CBitmap::FromHandle(hBMP));
						dcStretchImage.StretchBlt(0, 0, r.Width(), r.Height(), &dcBaseImage, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
						dcBaseImage.SelectObject(obbmp);
						dcStretchImage.SelectObject(osbmp);
						DrawTransparentBitmap(dc.GetSafeHdc(), (HBITMAP)stretchBmp.GetSafeHandle(), 0, 0,
							r.Width(), r.Height(), m_transRGB);
					}
					else
					{
						CPoint pt = r.TopLeft();
						if ((GetStyle() & SS_CENTERIMAGE) == SS_CENTERIMAGE)
						{
							pt.x = r.CenterPoint().x - bi.bmWidth/2;
							pt.y = r.CenterPoint().y - bi.bmHeight/2;
						}
						DrawTransparentBitmap(dc.GetSafeHdc(), hBMP, pt.x, pt.y, bi.bmWidth, bi.bmHeight, m_transRGB);
					}
				}
				else
				{
					CRgn rgn1, rgn2, rrgn;
					rgn1.CreateRectRgnIndirect(&r);
					rrgn.CreateRectRgnIndirect(&r);
					r.InflateRect(-2,-2);
					rgn2.CreateRectRgnIndirect(&r);
					rrgn.CombineRgn(&rgn1, &rgn2, RGN_DIFF);
					CBrush br(m_frameRGB);
					dc.FillRgn(&rrgn, &br);
				}
				return TRUE;
			}
			break;
		}
		return CWnd::WindowProc(message, wParam, lParam);
	}
};

#pragma warning (disable : 4311)

template <typename TBase>
class CManagedWnd : public TBase, public CTrapKeys
{
public:
	CManagedWnd(UINT nIDTemplate, CWnd* pParentWnd = NULL) : TBase(nIDTemplate, pParentWnd),
		m_bModal(true),	m_bAlwaysVisible(true), m_bRegisterManaged(false), m_handle(0)

	{ }
	CManagedWnd() :
	m_bModal(true), m_bAlwaysVisible(true), m_handle(0)
	{ }
	void SetManagedDialogType(LPCTSTR sName, bool bModal, bool bAlwaysVisible = true)
	{
		m_sName = sName;
		m_bModal = bModal;
		m_bAlwaysVisible = bAlwaysVisible;
		m_bRegisterManaged = true;
	}
	void FlushEvents()
	{
		MSG		msg;
		bool    bDone = false;
		int counter = 0;
		do
		{
			if (::PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
				bDone = true;
			if (++counter > 1024)
				bDone = true; // Get out if we reach a message re-queue loop.
		}
		while( !bDone);
	}
	virtual INT_PTR DoModal()
	{
		FlushEvents();
		INT_PTR iRet = (INT_PTR) TBase::DoModal();
		FlushEvents();
		return iRet;
	}
	virtual void GetContextHelp(POINT pt, int id, int* iContextID) { }
	virtual void GetBalloonHelp(POINT pt, int id, int subid, char* sBalloonHelp, int* iPos) { }
	virtual void ShowTheWindow(int nShow)
	{
		if (nShow)
		{
			if (IsWindowVisible() && m_handle && !m_bModal)
				gc_ShowManagedWindow(m_handle, SW_RESTORE);
			SetWindowPos(0, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_SHOWWINDOW);
		}
		else
		{
			SetWindowPos(0, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_HIDEWINDOW);
		}
	}
	void virtual OnHide()
	{
		//call your process close callback here (which we assume it actually destroys the dialog)
	}
public:
	static CStringW ToWideString(CStringA as)
	{
		CStringW ws;
		ULONG inlen = as.GetLength();
		int outlen = _mbstowcsz(ws.GetBuffer(2*inlen+1), (const char*)(as), 2*inlen+1);
		ws.ReleaseBuffer();
		return ws;
	}

	static CStringA ToMBString(CStringW ws)
	{
		CStringA as;
		ULONG inlen = ws.GetLength();
		int outlen = _wcstombsz(as.GetBuffer(2*inlen+1), (const wchar_t*)(ws), 2*inlen+1);
		as.ReleaseBuffer();
		return as;
	}

protected:
	CString m_sName;
	CString m_sContextName;
	bool    m_bModal;
	bool    m_bAlwaysVisible;
	bool    m_bRegisterManaged;
	virtual void GetBalloonId(POINT pt, int* id, int* subid)
	{
		if (id)
		{
			int iid=*id;
			int isid = (subid) ? *subid : 0;
			int iPos = 0;
			char str[256] = {0};
			GetBalloonHelp(pt, iid, isid, str, &iPos);
			if (str[0] || (iPos == -1))
				return;
		}
		if (subid)
			*subid = -1;
	}
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_INITDIALOG)
		{
			LRESULT rc = TBase::WindowProc(message, wParam, lParam);
			SubClassEdits(this, m_bModal ? false : true); //We don't need to subclass edits to control event propagation for modal dialogs.

			if (m_bRegisterManaged)
			{
#ifdef UNICODE
				gc_ManageWindow(GetSafeHwnd(), ToMBString(m_sName), m_bModal ? 1 : 0, &m_handle);
#else
				gc_ManageWindow(GetSafeHwnd(), m_sName, m_bModal ? 1 : 0, &m_handle);
#endif
			}
			return rc;
		}
		else if (message == WM_WINDOWPOSCHANGED)
		{
			LPWINDOWPOS lpwp = (LPWINDOWPOS) lParam;
#ifndef SM_CXVIRTUALSCREEN
#define SM_CXVIRTUALSCREEN 78
#endif
#ifndef SM_CYVIRTUALSCREEN
#define SM_CYVIRTUALSCREEN 79
#endif
#ifndef SM_XVIRTUALSCREEN
#define SM_XVIRTUALSCREEN 76
#endif
#ifndef SM_YVIRTUALSCREEN
#define SM_YVIRTUALSCREEN 77
#endif
			if (m_bAlwaysVisible && (lpwp->flags & SWP_SHOWWINDOW))
			{
				int vx = GetSystemMetrics(SM_XVIRTUALSCREEN);
				int vy = GetSystemMetrics(SM_YVIRTUALSCREEN);
				int mx = GetSystemMetrics(SM_CXVIRTUALSCREEN);
				if (!mx)
					mx = GetSystemMetrics(SM_CXSCREEN);
				int my = GetSystemMetrics(SM_CYVIRTUALSCREEN);
				if (!my)
					my = GetSystemMetrics(SM_CYSCREEN);
				CRect wr;
				GetWindowRect(&wr);
				CPoint pt = wr.TopLeft();
				if (wr.right < vx)
					pt.x = vx;
				if (wr.bottom < vy)
					pt.y = vy;
				if (pt.x > vx+mx)
					pt.x = vx+mx - wr.Width();
				if (pt.y > vy+my)
					pt.y = vy+my - wr.Height();
				SetWindowPos(0, pt.x, pt.y, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
			}
			else if (lpwp->flags & SWP_HIDEWINDOW)
			{
				LRESULT rc = TBase::WindowProc(message, wParam, lParam);
				OnHide();
				return rc;
			}

		}
		else if (message == WM_DESTROY)
		{
			if (m_bRegisterManaged)
				gc_UnmanageWindow(m_handle);
		}
		return TBase::WindowProc(message, wParam, lParam);
	}
	virtual BOOL PreTranslateMessage(MSG* pMSG)
	{
		const int	kCommand_B = 2; //Ctrl+B

		//		IsDialogMessage(pMSG);
		//		if (IsDialogMessage(pMSG))
		//			return TRUE;

		switch( pMSG->message )
		{
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_SYSCHAR:
			return TBase::PreTranslateMessage(pMSG); //FALSE;
		case WM_CHAR:
			if ( m_bModal && (pMSG->wParam == kCommand_B) )
			{
				if (GetOwner() && GetOwner()->GetSafeHwnd() == pMSG->hwnd)
					return TRUE;
				int bBalloonHelp;
				gc_GetBalloonHelp(&bBalloonHelp);
				gc_SetBalloonHelp(bBalloonHelp ? 0 : 1);
				return TRUE;
			}
			return TBase::PreTranslateMessage(pMSG); //FALSE;
		}
		return TBase::PreTranslateMessage(pMSG);
	}

	CWnd* TraverseDlgItem(CWnd *wnd, int id)
	{
		CWnd* ctl = (wnd->GetDlgCtrlID() == id) ? wnd : nullptr;
		if (!ctl)
			for (CWnd* cwnd = wnd->GetWindow(GW_CHILD); cwnd && !ctl; cwnd = cwnd->GetWindow(GW_HWNDNEXT))
				ctl = TraverseDlgItem(cwnd, id);
		return ctl;
	}

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
	{
		gc_teBalloonMsgType type;
		int *id=0, *subid = 0, *iPos=0;
		char* str=0;
		if (!gc_HandleBalloonHelp(WM_NOTIFY, (void*)lParam, &type, &id, &subid, &iPos, &str))
		{
			if ((type == eBalloonMsgType_GetText) && str && iPos && id)
			{
				CWnd* cw = TraverseDlgItem(this, *id);
				if (cw)
				{
					POINT pt;
					GetCursorPos(&pt);
					if (gc_GetToolTipIDMode())
					{
						CStringA s;
						int iContextID = 0;
						GetContextHelp(pt, *id, &iContextID);
						if (iContextID < 0) iContextID = 0;
						s.Format("ContextID %d", iContextID);
						strcpy(str, (LPCSTR) s);
					}
					else
					{
						GetBalloonHelp(pt, *id, *subid, str, iPos);
					}
					return TRUE;
				}
			}
			else if ((type == eBalloonMsgType_GetID) && id && subid)
			{
				POINT pt;
				GetCursorPos(&pt);
				GetBalloonId(pt, id, subid);
			}
			else if (type == eBalloonMsgType_GetContextID && iPos && str)
			{
				if (m_sContextName.GetLength())
				{
#ifdef UNICODE
					strcpy(str, ToMBString(m_sContextName));
#else
					strcpy(str, m_sContextName);
#endif
				}
				else
				{
#ifdef UNICODE
					strcpy(str, ToMBString(m_sName));
#else
					strcpy(str, m_sName);
#endif
				}
				CWnd* cw = TraverseDlgItem(this, *id);
				if (cw)
				{
					POINT pt;
					GetCursorPos(&pt);
					GetContextHelp(pt, *id, iPos);
					if (*iPos < 0)
						*iPos = 0;
					return TRUE;
				}
			}
		}
		return TBase::OnNotify(wParam, lParam, pResult);
	}
	int m_handle;

public:
	int GetWindowIndex(void) { return m_handle; }
};
#pragma warning (default : 4311)

class CManagedPropertySheet : public CManagedWnd<CPropertySheet>
{
	// Construction
public:
	CManagedPropertySheet(UINT nIDTemplate, CWnd* pParentWnd = NULL, UINT iSelectPage = 0 )
	{
		Construct(nIDTemplate, pParentWnd, iSelectPage);
	}
	CManagedPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0 )
	{
		Construct(pszCaption, pParentWnd, iSelectPage);
	}
	virtual ~CManagedPropertySheet() 
	{
	}
};

class CManagedPropertyPage : public CManagedWnd<CPropertyPage>
{
	// Construction
public:
	CManagedPropertyPage()
	{
		m_bAlwaysVisible = false;
		m_bRegisterManaged = false;
	}

	CManagedPropertyPage( UINT nIDTemplate, UINT nIDCaption = 0 )
	{
		Construct( nIDTemplate, nIDCaption );
		m_bAlwaysVisible = false;
		m_bRegisterManaged = false;
	}

	CManagedPropertyPage( LPCTSTR lpszTemplateName, UINT nIDCaption = 0 )
	{
		Construct( lpszTemplateName, nIDCaption );
		m_bAlwaysVisible = false;
		m_bRegisterManaged = false;
	}
	virtual ~CManagedPropertyPage() 
	{
	}
};

class CManagedDialog : public CManagedWnd<CDialog>
{
	// Construction
public:
	CManagedDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL ) : CManagedWnd<CDialog>(nIDTemplate, pParentWnd)
	{
	}
	virtual ~CManagedDialog() 
	{
	}
};

#define DECLARE_BALLOON_MAP() \
	virtual void GetBalloonHelp(POINT pt, int id, int subid, char* sBalloonHelp, int* iPos);









#define BEGIN_BALLOON_MAP(cls) \
	void  cls::GetBalloonHelp(POINT pt, int id, int subid, char* sBalloonHelp, int* iPos) \
{	\
	BalloonHelpMap bhmap[] = {

#define END_BALLOON_MAP() \
}; \
	BalloonHelpMap::ProcessMap(id, subid, bhmap, sizeof(bhmap)/sizeof(BalloonHelpMap), sBalloonHelp, iPos); \
}

#define BALLOON_MAP(cid, sid, pos) \
{cid, -1, sid, -1, pos},

#define DECLARE_DYNAMIC_BALLOON_MAP() \
	virtual void GetBalloonHelp(POINT pt, int id, int subid, char* sBalloonHelp, int* iPos); \
	void ChangeBalloonMap(int index, int cid, int sid, int pos);

#define BEGIN_DYNAMIC_BALLOON_MAP() \
	static BalloonHelpMap bhmap[] = {

#define DYNAMIC_BALLOON_MAP(cid, sid, pos) \
{cid, -1, sid, -1, pos},

#define END_DYNAMIC_BALLOON_MAP(cls) \
}; \
	void  cls::GetBalloonHelp(POINT pt, int id, int subid, char* sBalloonHelp, int* iPos) \
{	\
	BalloonHelpMap::ProcessMap(id, subid, bhmap, sizeof(bhmap)/sizeof(BalloonHelpMap), sBalloonHelp, iPos); \
}	\
	void  cls::ChangeBalloonMap(int index, int cid, int sid, int pos) \
{	\
	bhmap[index].ctlID = cid; \
	bhmap[index].strID = sid; \
	bhmap[index].iPos = pos; \
}

#define DECLARE_CONTEXT_MAP() \
	virtual void GetContextHelp(POINT pt, int id, int* iContextID);

#define BEGIN_CONTEXT_MAP(cls, ctxt) \
	void  cls::GetContextHelp(POINT pt, int id, int* iContextID) \
{	\
	m_sContextName = ctxt; \
	ContextHelpMap chmap[] = {

#define END_CONTEXT_MAP() \
}; \
	ContextHelpMap::ProcessMap(id, chmap, sizeof(chmap)/sizeof(ContextHelpMap), iContextID); \
}

#define CONTEXT_MAP(cid, sid) \
{cid, sid},

#define DECLARE_DYNAMIC_CONTEXT_MAP() \
	virtual void GetContextHelp(POINT pt, int id, int* iContextID); \
	void ChangeContextMap(int index, int cid, int sid);

#define BEGIN_DYNAMIC_CONTEXT_MAP() \
	static ContextHelpMap chmap[] = {

#define DYNAMIC_CONTEXT_MAP(cid, sid) \
{cid, sid},

#define END_DYNAMIC_CONTEXT_MAP(cls, ctxt) \
}; \
	void  cls::GetContextHelp(POINT pt, int id, int* iContextID) \
{	\
	ContextHelpMap::ProcessMap(id, chmap, sizeof(chmap)/sizeof(ContextHelpMap), iContextID); \
	m_sContextName = ctxt; \
}	\
	void  cls::ChangeContextMap(int index, int cid, int sid) \
{	\
	chmap[index].ctlID = cid; \
	chmap[index].ctextID = sid; \
}

class CResizeableManagedDialog : public CManagedDialog
{
public:
	enum {
		KEEPTOP    = 0x01,
		KEEPBOTTOM = 0x02,
		KEEPLEFT   = 0x04,
		KEEPRIGHT  = 0x08,
		KEEPWIDTH  = 0x10,
		KEEPHEIGHT = 0x20,
		KEEPALIGN  = 0x40
	} ResizeFlags;

	class CWindowResizeItem
	{
	public:
		CWindowResizeItem(HWND hwnd, int resizeFlags)
		{
			m_hWnd = hwnd;
			m_resizeFlags = resizeFlags;
			RECT cr;
			::GetWindowRect(m_hWnd, &cr);
			m_w = double(cr.right-cr.left);
			m_h = double(cr.bottom-cr.top);
			m_hLast = m_h;
			POINT pt;
			pt.x = cr.left;
			pt.y = cr.top;
			::ScreenToClient(::GetParent(m_hWnd), &pt);
			m_x = double(pt.x);
			m_y = double(pt.y);
			m_yLast = m_y;
			m_hInitial = 0.0;
		}
		virtual ~CWindowResizeItem()
		{
		}

		HWND GetWindowHandle() { return m_hWnd; }
		void SetResizeFlags(int resizeFlags) {	m_resizeFlags = resizeFlags; }
		void CalculateResize(SIZE  *oldnew, POINT mousePos, int &iLastResize, RECT* outRect = 0)
		{
			double x1, x2, y1, y2;

			if (oldnew[0].cx == 0 || oldnew[0].cy == 0)
				return;
			double dx = ((double) oldnew[1].cx) / ((double) oldnew[0].cx);
			double dy = ((double) oldnew[1].cy) / ((double) oldnew[0].cy);
			if (m_resizeFlags & CResizeableManagedDialog::KEEPLEFT)
				x1 = m_x;
			else
				x1 = dx * m_x;
			if (m_resizeFlags & CResizeableManagedDialog::KEEPRIGHT)
			{
				x2 = ((double)oldnew[1].cx) - (((double)oldnew[0].cx)-(m_x+m_w));
			}
			else
			{
				x2 = dx * (m_x + m_w);
				if (m_resizeFlags & CResizeableManagedDialog::KEEPLEFT)
				{
					double xtmp = dx * m_x;
					x2 -= xtmp - x1;
				}
			}
			if (m_resizeFlags & CResizeableManagedDialog::KEEPTOP)
			{
				y1 = m_y;

				if (m_resizeFlags & CResizeableManagedDialog::KEEPALIGN)
				{
					if (mousePos.y < m_y)
						iLastResize = 0;
					else
						iLastResize = 1;
				}
			}
			else
				y1 = dy * m_y;
			if (m_resizeFlags & CResizeableManagedDialog::KEEPBOTTOM)
			{
				y2 = ((double)oldnew[1].cy) - (((double)oldnew[0].cy)-(m_y+m_h));
				
				if (m_resizeFlags & CResizeableManagedDialog::KEEPALIGN)
				{
					//if (mousePos.y > (m_y + m_h)) iLastResize = 2;  /***mousePos may change during WM_RESIZE***/
					//if (iLastResize == 0 || iLastResize == 1)  //KEEPHEIGHT
					if (iLastResize == 0)  //KEEPHEIGHT
					{
						if (m_hInitial > 0.0)	//use the initial value
						{
							m_hLast = m_hInitial;
							m_hInitial = 0.0;
						}

						y1 = y2 - m_hLast;
					}
					else
					{
						y1 = ((double)oldnew[1].cy) - (((double)oldnew[2].cy) - m_hLast);
						m_hLast = y2 - y1;
					}
				}
			}
			else
			{
			    y2 = dy * (m_y + m_h);
				if (m_resizeFlags & CResizeableManagedDialog::KEEPTOP)
				{
					double ytmp = dy * m_y;
					y2 -= ytmp - y1;

					if (m_resizeFlags & CResizeableManagedDialog::KEEPALIGN)
					{
						if (iLastResize == 0)
						{
							if (m_hInitial > 0.0)//use the initial value
							{
								y2 = y1 + m_hInitial;
								m_hLast = m_hInitial;
								m_hInitial = 0.0;
							}
							else
							{
								y2 = ((double)oldnew[1].cy) - (((double)oldnew[2].cy) - (m_y + m_hLast));
								m_hLast = y2 - y1;
							}
						}
						else
							y2 = y1 + m_hLast;
					}
				}
			}
			if (m_resizeFlags & CResizeableManagedDialog::KEEPHEIGHT)
			{
				if (m_resizeFlags & CResizeableManagedDialog::KEEPBOTTOM)
					y1 = y2 - m_h;
				else
					y2 = y1 + m_h;

				if (m_resizeFlags & CResizeableManagedDialog::KEEPALIGN)
				{
					if (iLastResize == 0)
					{
						if (m_hInitial > 0.0)//use the initial value
						{
							y1 = m_hInitial;
							m_hInitial = 0.0;
						}
						else
							y1 = ((double)oldnew[1].cy) - (((double)oldnew[2].cy) - m_yLast);

						m_yLast = y1;
					}
					else 
						y1 = m_yLast;
					y2 = y1 + m_h;
				}
			}
			if (m_resizeFlags & CResizeableManagedDialog::KEEPWIDTH)
			{
				if (m_resizeFlags & CResizeableManagedDialog::KEEPRIGHT)
					x1 = x2 - m_w;
				else
					x2 = x1 + m_w;
			}
			int newx = int(x1 + 0.5);
			int newy = int(y1+0.5);
			int neww = int((x2-x1)+0.5);
			int newh = int((y2-y1)+0.5);
			if (!outRect)
				::MoveWindow(m_hWnd, newx, newy, neww, newh, TRUE);
			else
			{
				outRect->left   = newx;
				outRect->top    = newy;
				outRect->right  = newx+neww;
				outRect->bottom = newy+newh;
			}
		}
		void GetResizeItemInfo(SIZE * itemSize, double &dItemHeight, double &dItemTop)
		{
			itemSize->cx = (LONG)m_w;
			itemSize->cy = (LONG)m_h;
			dItemHeight = m_hLast;
			dItemTop = m_yLast;
			return;
		}

		void SetResizeItemInfo(double dInitial)
		{
			m_hInitial = dInitial;
			return;
		}

	protected:
		double m_x, m_y, m_w, m_h, m_hLast, m_yLast, m_hInitial;
		HWND   m_hWnd;
		int    m_resizeFlags;
	};

	CResizeableManagedDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL ) : CManagedDialog(nIDTemplate, pParentWnd)
	{
		m_originalSize.cx = 1;
		m_originalSize.cy = 1;
		m_lastSize.cx = 1;
		m_lastSize.cy = 1;
		m_LastResize = 0;
	}

	virtual ~CResizeableManagedDialog( )
	{
		for (int i = 0; i < (int)m_clientList.size(); i++)
			delete m_clientList[i];
	}

	void ManageControl(HWND ctl=0, int resizeFlags=0)
	{
		if (!ctl)
		{
			for (int i = 0; i < (int)m_clientList.size(); i++)
				delete m_clientList[i];
			m_clientList.clear();
			for (HWND cw = ::GetWindow(m_hWnd, GW_CHILD); cw; cw = cw = ::GetWindow(cw, GW_HWNDNEXT))
				ManageControl(cw, resizeFlags);
		}
		else
		{
			CWindowResizeItem* item = GetManagedControl(ctl);
			if (item)
				item->SetResizeFlags(resizeFlags);
			else
			{
				CWindowResizeItem *ResizeItem = new CWindowResizeItem(ctl, resizeFlags);
				m_clientList.push_back(new CWindowResizeItem(ctl, resizeFlags));
			}
		}
	}

	void ManageControl(int ictl=0, int resizeFlags=0)
	{
		ManageControl(::GetDlgItem(m_hWnd, ictl), resizeFlags);
	}

	void DeleteManagedControl(HWND ctl)
	{
		for (int i = 0; i < (int)m_clientList.size(); i++)
			if (m_clientList[i]->GetWindowHandle() == ctl)
			{
				m_clientList.erase(m_clientList.begin()+i);
				return;
			}
	}

	CWindowResizeItem* GetManagedControl(HWND ctl)
	{
		for (int i = 0; i < (int)m_clientList.size(); i++)
			if (m_clientList[i]->GetWindowHandle() == ctl)
				return m_clientList[i];
		return 0;
	}

	void GetManagedControlInfo(int ictl, SIZE * controlSize, double &dCurrentHeight, double &dCurrentTop)
	{	
		controlSize->cx = 0;
		controlSize->cy = 0;
		dCurrentHeight = 0.0;
		dCurrentTop = 0.0;

		HWND ctl = ::GetDlgItem(m_hWnd, ictl);

		for (int i = 0; i < (int)m_clientList.size(); i++)
			if (m_clientList[i]->GetWindowHandle() == ctl)
			{
			m_clientList[i]->GetResizeItemInfo(controlSize, dCurrentHeight, dCurrentTop);
				return;
			}
		return;
	}

	void SetManagedControlInfo(int ictl, double dInitial)
	{
		HWND ctl = ::GetDlgItem(m_hWnd, ictl);

		for (int i = 0; i < (int)m_clientList.size(); i++)
			if (m_clientList[i]->GetWindowHandle() == ctl)
			{
				m_clientList[i]->SetResizeItemInfo(dInitial);
				return;
			}
		return;
	}

	void GetManagedControlDialogInfo(SIZE * dialogSize)
	{
		dialogSize->cx = m_lastSize.cx;
		dialogSize->cy = m_lastSize.cy;

		return;
	}

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_INITDIALOG)
		{
			RECT cr;
			GetWindowRect(&cr);
			m_originalSize.cx = cr.right-cr.left;
			m_originalSize.cy = cr.bottom-cr.top;
			m_lastSize.cx = cr.right - cr.left;
			m_lastSize.cy = cr.bottom - cr.top;
			return CManagedDialog::WindowProc(message, wParam, lParam);
		}
		else if (message == WM_SIZE)
		{
			SIZE oldnew[3];
			oldnew[0] = m_originalSize;
			RECT r;
			GetWindowRect(&r);

			if ((r.bottom - r.top) == 26)	//dialog is rolled-up -- no need to resize
				return CManagedDialog::WindowProc(message, wParam, lParam);

			oldnew[1].cx = r.right-r.left;
			oldnew[1].cy = r.bottom-r.top;
			oldnew[2] = m_lastSize;

			HDWP dwp = BeginDeferWindowPos((int)m_clientList.size());
			for (int i = 0; i < (int)m_clientList.size(); i++)
			{
				m_clientList[i]->CalculateResize(oldnew, m_mousePos, m_LastResize, &r);
				dwp = DeferWindowPos(dwp, m_clientList[i]->GetWindowHandle(),
					//				::SetWindowPos(m_clientList[i]->GetWindowHandle(), 
					0, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_NOACTIVATE | SWP_NOZORDER);
			}
			m_lastSize.cx = oldnew[1].cx;	//last window size
			m_lastSize.cy = oldnew[1].cy;

			// Resize the size grip
			if (m_SizeGrip.m_hWnd != NULL)
			{
				int nSize = GetSystemMetrics(SM_CXVSCROLL);
				CRect clientRect;
				GetClientRect(&clientRect);
				dwp = DeferWindowPos(dwp, m_SizeGrip.GetSafeHwnd(), 0,
					clientRect.right - nSize,
					clientRect.bottom - nSize,
					nSize,
					nSize,
					SWP_NOZORDER | SWP_SHOWWINDOW);
			}
			EndDeferWindowPos(dwp);

		}
		else if (message == WM_CREATE)
		{
			CRect clientRect;
			GetClientRect(&clientRect);

			int nSize = GetSystemMetrics(SM_CXVSCROLL);
			CRect grippieRect;
			grippieRect.right=clientRect.right;
			grippieRect.bottom=clientRect.bottom;
			grippieRect.left=clientRect.right - nSize;
			grippieRect.top=clientRect.bottom - nSize;

			// Create the size grip
			m_SizeGrip.Create(WS_CHILD|WS_VISIBLE|SBS_SIZEGRIP|WS_CLIPSIBLINGS,
				grippieRect, this, 0);
		}
		else if (message == WM_NCHITTEST)
		{
			CRect r;

			GetClientRect(&r);

			int nSize = GetSystemMetrics(SM_CXVSCROLL);
			r.left = r.right - nSize;
			r.top = r.bottom - nSize;
			POINTS pts = MAKEPOINTS(lParam);
			POINT pt;
			pt.x = pts.x;
			pt.y = pts.y;
			ScreenToClient(&pt);

			m_mousePos.x = pt.x;
			m_mousePos.y = pt.y;

			if (r.PtInRect(pt))
				return HTBOTTOMRIGHT;
		}
		return CManagedDialog::WindowProc(message, wParam, lParam);
	}
	SIZE m_maxSize;
	SIZE m_minSize;
	SIZE m_originalSize, m_lastSize;
	POINT m_mousePos;
	std::vector<CWindowResizeItem*> m_clientList;
	CScrollBar m_SizeGrip;
	int m_LastResize;
};


//Helper class for modal interrogation support.
class CMousePressModalWrapper
{
public:
	CMousePressModalWrapper()
	{
#if (_WIN32_WINNT >= 0x0400)
		HHOOK hhook = ::SetWindowsHookEx( WH_MOUSE_LL, MouseProc, AfxGetInstanceHandle(), 0); //, 0 ); //GetCurrentThreadId() );
#else
		HHOOK hhook = ::SetWindowsHookEx( WH_MOUSE, MouseProc, AfxGetInstanceHandle(), 0); //, 0 ); //GetCurrentThreadId() );
#endif
		AccessHook(&hhook);
	}
	virtual ~CMousePressModalWrapper()
	{
		if (AccessHook())
			Stop();
	}
	static HHOOK AccessHook( HHOOK* hhook = 0)
	{
		static HHOOK g_hhook = 0;
		if (hhook)
			g_hhook = *hhook;
		return g_hhook;
	}
	static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		if (nCode == HC_ACTION)
		{
#if (_WIN32_WINNT >= 0x0400)
			MSLLHOOKSTRUCT* mhs = (MSLLHOOKSTRUCT*)lParam;
#else
			MOUSEHOOKSTRUCT* mhs = (MOUSEHOOKSTRUCT*)lParam;
#endif
			if (wParam == WM_LBUTTONDOWN)
			{
				POINT pt = mhs->pt;
				int iRef, iSolid;
				gc_TopoId FeatureRef;
				if (!gc_PickGeoSol( true, pt.x, pt.y, &iRef, &iSolid, &FeatureRef ))
				{
					int xy[2] = {pt.x, pt.y};
					gc_InterrogateGeo(xy);
				}
			}
		}
		return ::CallNextHookEx(AccessHook(), nCode, wParam, lParam);
	}
	static void Stop()
	{
		if (AccessHook())
			VERIFY (::UnhookWindowsHookEx (AccessHook()));
		HHOOK hh=0;
		AccessHook(&hh);
	}
};
#else
class CManagedEditCtrl
{
public:
	typedef enum
	{
		eShort,
		eDouble,
		eInt
	} teDataType;
};
#endif _MFC_VER
#endif
