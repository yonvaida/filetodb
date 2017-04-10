
// File_to_DB.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFile_to_DBApp:
// See File_to_DB.cpp for the implementation of this class
//

class CFile_to_DBApp : public CWinApp
{
public:
	CFile_to_DBApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFile_to_DBApp theApp;
