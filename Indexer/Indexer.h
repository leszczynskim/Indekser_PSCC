
// Indexer.h : main header file for the Indexer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CIndexerApp:
// See Indexer.cpp for the implementation of this class
//

class CIndexerApp : public CWinApp
{
public:
	CIndexerApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIndexerApp theApp;
