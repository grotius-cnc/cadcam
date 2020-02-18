/*
 *	opengl.h
 *	OpenGL Demo
 *
 *	Created by Ross Ashman on Jan 1 2005.
 *	Copyright (c) 2005 Ross Ashman. All rights reserved.
 *
 */

// opengl.h: interface for the wxopengl class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _opengl_H__INCLUDED_
#define _opengl_H__INCLUDED_

#include <wx/glcanvas.h>
#include <wx/gdicmn.h>
#include <core/variable.h>
#include <wx/timer.h>
#include <wx/image.h>

class opengl : public wxGLCanvas
{
    wxTimer m_timer;

public:

	opengl(wxWindow* parent,
                   wxWindowID id = -1,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style=0,
                   const wxString& name=wxT("GLCanvas"),
                   int* attribList = 0,
                   const wxPalette& palette = wxNullPalette);

	virtual ~opengl();

	void InitGL();
	void update();
	void OnLeftMouse(wxMouseEvent& event);
	void OnLeftMouseUp(wxMouseEvent& event);
	void OnRightMouse(wxMouseEvent& event);
	void OnRightMouseUp(wxMouseEvent& event);
	void OnMiddleMouse(wxMouseEvent& event);
	void OnMiddleMouseUp(wxMouseEvent& event);
	void OnMiddleMouseWheel(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnSize(wxSizeEvent& event);
	void ontimer(wxTimerEvent & event);

    GLuint texture;

protected:

private:

	DECLARE_EVENT_TABLE()

      float RotX, RotY, Depth;
      long Xcoord, Ycoord, Zcoord, Dummy, X, Y;
      int MouseButton;
      struct MyColor {
        float R;
        float G;
        float B;
        } OColor, BColor;

};

#endif // _opengl_H__INCLUDED_
