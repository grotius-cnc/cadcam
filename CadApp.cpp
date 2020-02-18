/***************************************************************
 * Name:      CadApp.cpp
 * Purpose:   Code for Application Class
 * Author:    coder ()
 * Created:   2020-01-26
 * Copyright: coder ()
 * License:
 **************************************************************/

#include "CadApp.h"

//(*AppHeaders
#include "CadMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(CadApp);

bool CadApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CadFrame* Frame = new CadFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
