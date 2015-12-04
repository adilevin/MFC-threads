// progressbar1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// Cprogressbar1App:
// See progressbar1.cpp for the implementation of this class
//

class Cprogressbar1App : public CWinApp
{
public:
	Cprogressbar1App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cprogressbar1App theApp;