// $$root$$.h : main header file for the $$ROOT$$ application
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CServerApp:
// See $$root$$.cpp for the implementation of this class
//

class CServerApp : public CWinApp
{
public:
	CServerApp();

// Document view(s).
$$IF(WANTS_TEXTVIEW)
	CDocTemplate* pDocTxtTemplate;
$$ENDIF //WANTS_TEXTVIEW
	CDocTemplate* pDocTemplate ;
// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
protected:
	COleTemplateServer m_server;
	int m_iWantDefDoc ;
	CString m_DefaultDoc ;

	//{{AFX_MSG(CServerApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
