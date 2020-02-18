/***************************************************************
 * Name:      CadMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    coder ()
 * Created:   2020-01-26
 * Copyright: coder ()
 * License:
 **************************************************************/

#include "CadMain.h"
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>

#include <opengl.h>
#include <core/variable.h>

#include <dxf/read_dxf.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <debug/debug_cad_array.h>

//(*InternalHeaders(CadFrame)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/artprov.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

//timer
enum
{
    ID_TIMER //= wxID_HIGHEST + 1
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(CadFrame)
const long CadFrame::ID_PANEL1 = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_POINT = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_LINE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_LINESTRIP = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_RECTANGLE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_ARC = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_CIRCLE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_CIRCLE_3P = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_POLYGON = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_ELLIPSE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_CUBIC_BEZIER_CURVE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_SPLINE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_ENDPOINT = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_MIDPOINT = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_PERPENDICULAR = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_INTERSECTION = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_NEAREST = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_CIRCLECENTER = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_TANGENT = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_CIRCLE_4P = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_GRID = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_ortho = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_MOVE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_COPY = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_OFFSET = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_STRETCH = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_MIRROR = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_ROTATE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_SCALE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_EXTEND = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_TRIM = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_FILLED = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_CHAMFER = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_MATCH_PROPERTIES = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DIMENSION_HORIZONTAL = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DIMENSION_VERTICAL = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DIMENSION_NON_HORIZONTAL = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DIMENSION_DIAMETER = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DIMENSION_RADIUS = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DIMENSION_ANGLE_2P = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DIMENSION_ANGLE_3P = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DIMENSION_EDIT = wxNewId();
const long CadFrame::ID_PANEL3 = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_FILE_NEW = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_FILE_OPEN = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_FILE_SAVE_AS = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_PRINT = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_VIEW_3D = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_VIEW_TOP = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_VIEW_BOTTOM = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_VIEW_LEFT = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_VIEW_RIGHT = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_VIEW_FRONT = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_VIEW_BACK = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_VIEW_EXTEND = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_ZOOM_WINDOW = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_ZOOM_PLUS = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_ZOOM_MIN = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DELETE = wxNewId();
const long CadFrame::ID_BITMAPBUTTON4 = wxNewId();
const long CadFrame::ID_CHOICE2 = wxNewId();
const long CadFrame::ID_BITMAPBUTTON5 = wxNewId();
const long CadFrame::ID_CHOICE1 = wxNewId();
const long CadFrame::ID_BITMAPBUTTON6 = wxNewId();
const long CadFrame::ID_CHOICE3 = wxNewId();
const long CadFrame::ID_BITMAPBUTTON60 = wxNewId();
const long CadFrame::ID_BITMAPBUTTON61 = wxNewId();
const long CadFrame::ID_PANEL2 = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_CAD = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_CAM = wxNewId();
const long CadFrame::ID_BITMAPBUTTON_DEBUG = wxNewId();
const long CadFrame::ID_PANEL4 = wxNewId();
const long CadFrame::ID_TEXTCTRL_message = wxNewId();
const long CadFrame::ID_TEXTCTRL_USER_INPUT = wxNewId();
const long CadFrame::ID_TEXTCTRL_MOUSE_POS_X = wxNewId();
const long CadFrame::ID_TEXTCTRL_MOUSE_POS_Y = wxNewId();
const long CadFrame::ID_PANEL5 = wxNewId();
//*)



BEGIN_EVENT_TABLE(CadFrame,wxFrame)
    //(*EventTable(CadFrame)
    //*)
    EVT_TIMER(ID_TIMER, CadFrame::OnSpinTimer)
END_EVENT_TABLE()

CadFrame::CadFrame(wxWindow* parent,wxWindowID id) : m_spinTimer(this,ID_TIMER)
{
    m_spinTimer.Start(10);

    //(*Initialize(CadFrame)
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer9;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;

    Create(parent, wxID_ANY, _("CADCAM -- Powered by Linux 2020 --"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1000,900));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("/home/user/Cad/icons/cadcam.png"))));
    	SetIcon(FrameIcon);
    }
    AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    Panel1 = new opengl(this, ID_PANEL1, wxPoint(406,523), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(200,200));
    AuiManager1->AddPane(Panel1, wxAuiPaneInfo().Name(_T("PaneName")).DefaultPane().Caption(_("Pane caption")).CaptionVisible(false).CloseButton(false).Center().MinSize(wxSize(200,200)));
    Panel3 = new wxPanel(this, ID_PANEL3, wxPoint(17,44), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel3->SetMinSize(wxSize(64,0));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer5 = new wxBoxSizer(wxVERTICAL);
    BitmapButton_point = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_POINT, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/point.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_POINT"));
    BitmapButton_point->SetToolTip(_("point"));
    BoxSizer5->Add(BitmapButton_point, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_line = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_LINE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/line.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_LINE"));
    BitmapButton_line->SetToolTip(_("line"));
    BoxSizer5->Add(BitmapButton_line, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_linestrip = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_LINESTRIP, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/linestrip.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_LINESTRIP"));
    BitmapButton_linestrip->SetToolTip(_("linestrip"));
    BoxSizer5->Add(BitmapButton_linestrip, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton1_rectangle = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_RECTANGLE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/rectangle.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_RECTANGLE"));
    BitmapButton1_rectangle->SetToolTip(_("rectangle"));
    BoxSizer5->Add(BitmapButton1_rectangle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_arc = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_ARC, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/arc.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_ARC"));
    BitmapButton_arc->SetToolTip(_("arc"));
    BoxSizer5->Add(BitmapButton_arc, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_circle = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_CIRCLE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/circle.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CIRCLE"));
    BitmapButton_circle->SetToolTip(_("circle"));
    BoxSizer5->Add(BitmapButton_circle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_circle_3p = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_CIRCLE_3P, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/circle_3p.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CIRCLE_3P"));
    BitmapButton_circle_3p->SetToolTip(_("circle_3p"));
    BoxSizer5->Add(BitmapButton_circle_3p, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_polygon = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_POLYGON, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/polygon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_POLYGON"));
    BitmapButton_polygon->SetToolTip(_("polygon"));
    BoxSizer5->Add(BitmapButton_polygon, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_ellipse = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_ELLIPSE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/ellipse.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_ELLIPSE"));
    BitmapButton_ellipse->SetToolTip(_("ellipse"));
    BoxSizer5->Add(BitmapButton_ellipse, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_cubic_bezier_curve = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_CUBIC_BEZIER_CURVE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/cubicbezcurve.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CUBIC_BEZIER_CURVE"));
    BitmapButton_cubic_bezier_curve->SetToolTip(_("cubic_bezier_curve"));
    BoxSizer5->Add(BitmapButton_cubic_bezier_curve, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_spline = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_SPLINE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/spline.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_SPLINE"));
    BitmapButton_spline->SetToolTip(_("spline"));
    BoxSizer5->Add(BitmapButton_spline, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_endpoint = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_ENDPOINT, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/endpoint.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_ENDPOINT"));
    BitmapButton_endpoint->SetToolTip(_("snap_endpoint"));
    BoxSizer5->Add(BitmapButton_endpoint, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_midpoint = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_MIDPOINT, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/midpoint.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_MIDPOINT"));
    BitmapButton_midpoint->SetToolTip(_("snap_midpoint"));
    BoxSizer5->Add(BitmapButton_midpoint, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_perpendicular = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_PERPENDICULAR, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/perpendicular.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_PERPENDICULAR"));
    BitmapButton_perpendicular->SetToolTip(_("snap_perpendicular"));
    BoxSizer5->Add(BitmapButton_perpendicular, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_intersection = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_INTERSECTION, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/intersection.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_INTERSECTION"));
    BitmapButton_intersection->SetToolTip(_("snap_intersection"));
    BoxSizer5->Add(BitmapButton_intersection, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_nearest = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_NEAREST, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/nearest.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_NEAREST"));
    BitmapButton_nearest->SetToolTip(_("snap_nearest"));
    BoxSizer5->Add(BitmapButton_nearest, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_circlecenter = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_CIRCLECENTER, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/circlecenter.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CIRCLECENTER"));
    BitmapButton_circlecenter->SetToolTip(_("snap_circlecenter"));
    BoxSizer5->Add(BitmapButton_circlecenter, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_tangent = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_TANGENT, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/tangent.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_TANGENT"));
    BitmapButton_tangent->SetToolTip(_("snap_circle_tangent"));
    BoxSizer5->Add(BitmapButton_tangent, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_circle_4p = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_CIRCLE_4P, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/circle_4p.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CIRCLE_4P"));
    BitmapButton_circle_4p->SetToolTip(_("snap_circle_4p"));
    BoxSizer5->Add(BitmapButton_circle_4p, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_grid = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_GRID, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/grid.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_GRID"));
    BitmapButton_grid->SetToolTip(_("grid"));
    BoxSizer5->Add(BitmapButton_grid, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_ortho = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_ortho, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/ortho.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_ortho"));
    BitmapButton_ortho->SetToolTip(_("ortho F8"));
    BoxSizer5->Add(BitmapButton_ortho, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer2->Add(BoxSizer5, 0, wxALL|wxEXPAND, 0);
    BoxSizer6 = new wxBoxSizer(wxVERTICAL);
    BitmapButton_move = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_MOVE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/move.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_MOVE"));
    BitmapButton_move->SetToolTip(_("move"));
    BoxSizer6->Add(BitmapButton_move, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_copy = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_COPY, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/copy.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_COPY"));
    BitmapButton_copy->SetToolTip(_("copy"));
    BoxSizer6->Add(BitmapButton_copy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_offset = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_OFFSET, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/offset.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_OFFSET"));
    BitmapButton_offset->SetToolTip(_("offset"));
    BoxSizer6->Add(BitmapButton_offset, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_stretch = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_STRETCH, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/stretch.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_STRETCH"));
    BitmapButton_stretch->SetToolTip(_("stretch"));
    BoxSizer6->Add(BitmapButton_stretch, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_mirror = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_MIRROR, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/mirror.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_MIRROR"));
    BitmapButton_mirror->SetToolTip(_("mirror"));
    BoxSizer6->Add(BitmapButton_mirror, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_rotate = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_ROTATE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/rotate.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_ROTATE"));
    BitmapButton_rotate->SetToolTip(_("rotate"));
    BoxSizer6->Add(BitmapButton_rotate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_scale = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_SCALE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/scale.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_SCALE"));
    BitmapButton_scale->SetToolTip(_("scale"));
    BoxSizer6->Add(BitmapButton_scale, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_extend = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_EXTEND, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/extend.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_EXTEND"));
    BitmapButton_extend->SetToolTip(_("extend"));
    BoxSizer6->Add(BitmapButton_extend, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_trim = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_TRIM, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/trim.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_TRIM"));
    BitmapButton_trim->SetToolTip(_("trim"));
    BoxSizer6->Add(BitmapButton_trim, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_filled = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_FILLED, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/filled.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_FILLED"));
    BitmapButton_filled->SetToolTip(_("fillet"));
    BoxSizer6->Add(BitmapButton_filled, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_chamfer = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_CHAMFER, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/chamfer.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CHAMFER"));
    BitmapButton_chamfer->SetToolTip(_("chamfer"));
    BoxSizer6->Add(BitmapButton_chamfer, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_match_properties = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_MATCH_PROPERTIES, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/match_properties.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_MATCH_PROPERTIES"));
    BitmapButton_match_properties->SetToolTip(_("match_properties"));
    BoxSizer6->Add(BitmapButton_match_properties, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_dimension_horizontal = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_DIMENSION_HORIZONTAL, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/horizontal.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DIMENSION_HORIZONTAL"));
    BoxSizer6->Add(BitmapButton_dimension_horizontal, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_dimension_vertical = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_DIMENSION_VERTICAL, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/vertical.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DIMENSION_VERTICAL"));
    BitmapButton_dimension_vertical->SetToolTip(_("dimension_vertical"));
    BoxSizer6->Add(BitmapButton_dimension_vertical, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_dimension_non_horizontal = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_DIMENSION_NON_HORIZONTAL, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/non_horizontal.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DIMENSION_NON_HORIZONTAL"));
    BitmapButton_dimension_non_horizontal->SetToolTip(_("dimension_lineair_angle"));
    BoxSizer6->Add(BitmapButton_dimension_non_horizontal, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_dimension_diameter = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_DIMENSION_DIAMETER, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/diameter.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DIMENSION_DIAMETER"));
    BitmapButton_dimension_diameter->SetToolTip(_("dimension_diameter"));
    BoxSizer6->Add(BitmapButton_dimension_diameter, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_dimension_radius = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_DIMENSION_RADIUS, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/radius.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DIMENSION_RADIUS"));
    BitmapButton_dimension_radius->SetToolTip(_("dimension_radius"));
    BoxSizer6->Add(BitmapButton_dimension_radius, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_dimension_angle_2p = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_DIMENSION_ANGLE_2P, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/angle_2p.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DIMENSION_ANGLE_2P"));
    BitmapButton_dimension_angle_2p->SetToolTip(_("dimension_angle_2p"));
    BoxSizer6->Add(BitmapButton_dimension_angle_2p, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_dimension_angle_3p = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_DIMENSION_ANGLE_3P, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/angle_3p.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DIMENSION_ANGLE_3P"));
    BitmapButton_dimension_angle_3p->SetToolTip(_("dimension_angle_3p"));
    BoxSizer6->Add(BitmapButton_dimension_angle_3p, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_dimension_edit = new wxBitmapButton(Panel3, ID_BITMAPBUTTON_DIMENSION_EDIT, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/dimension_edit.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DIMENSION_EDIT"));
    BitmapButton_dimension_edit->SetToolTip(_("dimension_edit"));
    BoxSizer6->Add(BitmapButton_dimension_edit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer2->Add(BoxSizer6, 0, wxALL|wxEXPAND, 0);
    Panel3->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel3);
    BoxSizer2->SetSizeHints(Panel3);
    AuiManager1->AddPane(Panel3, wxAuiPaneInfo().Name(_T("PaneName3")).DefaultPane().Caption(_("Pane caption")).CaptionVisible(false).CloseButton(false).Left().MinSize(wxSize(64,0)));
    Panel2 = new wxPanel(this, ID_PANEL2, wxPoint(0,0), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Panel2->SetMinSize(wxSize(0,64));
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    BitmapButton_file_new = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_FILE_NEW, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_FILE_NEW"));
    BitmapButton_file_new->SetToolTip(_("file_new"));
    BoxSizer8->Add(BitmapButton_file_new, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_file_open = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_FILE_OPEN, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_FILE_OPEN"));
    BitmapButton_file_open->SetToolTip(_("file_open"));
    BoxSizer8->Add(BitmapButton_file_open, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_file_save_as = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_FILE_SAVE_AS, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE_AS")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_FILE_SAVE_AS"));
    BitmapButton_file_save_as->SetToolTip(_("file_save_as"));
    BoxSizer8->Add(BitmapButton_file_save_as, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_print = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_PRINT, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_PRINT")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_PRINT"));
    BitmapButton_print->SetToolTip(_("print"));
    BoxSizer8->Add(BitmapButton_print, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_view_3d = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_VIEW_3D, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/3d.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_VIEW_3D"));
    BitmapButton_view_3d->SetToolTip(_("view_3d"));
    BoxSizer8->Add(BitmapButton_view_3d, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_view_top = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_VIEW_TOP, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/top.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_VIEW_TOP"));
    BitmapButton_view_top->SetToolTip(_("view_top"));
    BoxSizer8->Add(BitmapButton_view_top, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_view_bottom = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_VIEW_BOTTOM, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/bottom.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_VIEW_BOTTOM"));
    BitmapButton_view_bottom->SetToolTip(_("view_bottom"));
    BoxSizer8->Add(BitmapButton_view_bottom, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_view_left = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_VIEW_LEFT, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/left.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_VIEW_LEFT"));
    BitmapButton_view_left->SetToolTip(_("view_left"));
    BoxSizer8->Add(BitmapButton_view_left, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_view_right = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_VIEW_RIGHT, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/right.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_VIEW_RIGHT"));
    BitmapButton_view_right->SetToolTip(_("view_right"));
    BoxSizer8->Add(BitmapButton_view_right, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_view_front = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_VIEW_FRONT, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/front.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_VIEW_FRONT"));
    BitmapButton_view_front->SetToolTip(_("view_front"));
    BoxSizer8->Add(BitmapButton_view_front, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_view_back = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_VIEW_BACK, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/back.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_VIEW_BACK"));
    BitmapButton_view_back->SetToolTip(_("view_back"));
    BoxSizer8->Add(BitmapButton_view_back, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_view_extend = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_VIEW_EXTEND, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/zoom_extend.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_VIEW_EXTEND"));
    BitmapButton_view_extend->SetToolTip(_("zoom_extend"));
    BoxSizer8->Add(BitmapButton_view_extend, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_zoom_window = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_ZOOM_WINDOW, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/zoom_window.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_ZOOM_WINDOW"));
    BitmapButton_zoom_window->SetToolTip(_("zoom_window"));
    BoxSizer8->Add(BitmapButton_zoom_window, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_zoom_plus = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_ZOOM_PLUS, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/zoom_plus.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_ZOOM_PLUS"));
    BitmapButton_zoom_plus->SetToolTip(_("zoom_plus"));
    BoxSizer8->Add(BitmapButton_zoom_plus, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_zoom_min = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_ZOOM_MIN, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/zoom_min.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_ZOOM_MIN"));
    BitmapButton_zoom_min->SetToolTip(_("zoom_min"));
    BoxSizer8->Add(BitmapButton_zoom_min, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_delete = new wxBitmapButton(Panel2, ID_BITMAPBUTTON_DELETE, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/delete.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DELETE"));
    BitmapButton_delete->SetToolTip(_("delete"));
    BoxSizer8->Add(BitmapButton_delete, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer7->Add(BoxSizer8, 0, wxALL|wxEXPAND, 0);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    BitmapButton4 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON4, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/layer.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
    BoxSizer9->Add(BitmapButton4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Choice2 = new wxChoice(Panel2, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    Choice2->SetSelection( Choice2->Append(_("layer dimension")) );
    BoxSizer9->Add(Choice2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton5 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON5, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/linetype.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
    BoxSizer9->Add(BitmapButton5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Choice1 = new wxChoice(Panel2, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("solid")) );
    Choice1->Append(_("stipple"));
    BoxSizer9->Add(Choice1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton6 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON6, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/linewidth.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
    BoxSizer9->Add(BitmapButton6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Choice3 = new wxChoice(Panel2, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    Choice3->SetSelection( Choice3->Append(_("0mm")) );
    Choice3->Append(_("1mm"));
    Choice3->Append(_("2mm"));
    BoxSizer9->Add(Choice3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton60 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON60, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/text.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON60"));
    BoxSizer9->Add(BitmapButton60, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton61 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON61, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/text_edit.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON61"));
    BoxSizer9->Add(BitmapButton61, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer7->Add(BoxSizer9, 0, wxALL|wxEXPAND, 0);
    Panel2->SetSizer(BoxSizer7);
    BoxSizer7->Fit(Panel2);
    BoxSizer7->SetSizeHints(Panel2);
    AuiManager1->AddPane(Panel2, wxAuiPaneInfo().Name(_T("PaneName6")).DefaultPane().Caption(_("Pane caption")).CaptionVisible(false).CloseButton(false).Top().MinSize(wxSize(0,64)));
    Panel4 = new wxPanel(this, ID_PANEL4, wxPoint(36,782), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Panel4->SetMinSize(wxSize(32,0));
    BoxSizer10 = new wxBoxSizer(wxVERTICAL);
    BitmapButton_cad = new wxBitmapButton(Panel4, ID_BITMAPBUTTON_CAD, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/cad.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CAD"));
    BoxSizer10->Add(BitmapButton_cad, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_cam = new wxBitmapButton(Panel4, ID_BITMAPBUTTON_CAM, wxBitmap(wxImage(_T("/home/user/Cad_menu_test/icons/cam.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_CAM"));
    BoxSizer10->Add(BitmapButton_cam, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton_debug = new wxBitmapButton(Panel4, ID_BITMAPBUTTON_DEBUG, wxBitmap(wxImage(_T("/home/user/Cad/icons/debug.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DEBUG"));
    BoxSizer10->Add(BitmapButton_debug, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Panel4->SetSizer(BoxSizer10);
    BoxSizer10->Fit(Panel4);
    BoxSizer10->SetSizeHints(Panel4);
    AuiManager1->AddPane(Panel4, wxAuiPaneInfo().Name(_T("PaneName12")).DefaultPane().Caption(_("Pane caption")).CaptionVisible(false).Right().MinSize(wxSize(32,0)));
    Panel5 = new wxPanel(this, ID_PANEL5, wxPoint(36,989), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    Panel5->SetMinSize(wxSize(0,100));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    TextCtrl_message = new wxTextCtrl(Panel5, ID_TEXTCTRL_message, _(">> message"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_message"));
    BoxSizer3->Add(TextCtrl_message, 1, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND, 0);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    TextCtrl_user_input = new wxTextCtrl(Panel5, ID_TEXTCTRL_USER_INPUT, _(">> user input"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_USER_INPUT"));
    BoxSizer4->Add(TextCtrl_user_input, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_mouse_pos_x = new wxTextCtrl(Panel5, ID_TEXTCTRL_MOUSE_POS_X, _("0.000"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_MOUSE_POS_X"));
    BoxSizer4->Add(TextCtrl_mouse_pos_x, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_mouse_pos_y = new wxTextCtrl(Panel5, ID_TEXTCTRL_MOUSE_POS_Y, _("0.000"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_MOUSE_POS_Y"));
    BoxSizer4->Add(TextCtrl_mouse_pos_y, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer4, 0, wxALL|wxEXPAND, 0);
    Panel5->SetSizer(BoxSizer1);
    BoxSizer1->Fit(Panel5);
    BoxSizer1->SetSizeHints(Panel5);
    AuiManager1->AddPane(Panel5, wxAuiPaneInfo().Name(_T("PaneName11")).DefaultPane().Caption(_("Pane caption")).CaptionVisible(false).Bottom().MinSize(wxSize(0,100)));
    AuiManager1->Update();
    Center();

    Connect(ID_BITMAPBUTTON_POINT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_pointClick);
    Connect(ID_BITMAPBUTTON_LINE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_lineClick);
    Connect(ID_BITMAPBUTTON_LINESTRIP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_linestripClick);
    Connect(ID_BITMAPBUTTON_RECTANGLE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton1_rectangleClick);
    Connect(ID_BITMAPBUTTON_ARC,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_arcClick);
    Connect(ID_BITMAPBUTTON_CIRCLE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_circleClick);
    Connect(ID_BITMAPBUTTON_CIRCLE_3P,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_circle_3pClick);
    Connect(ID_BITMAPBUTTON_POLYGON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_polygonClick);
    Connect(ID_BITMAPBUTTON_ELLIPSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_ellipseClick);
    Connect(ID_BITMAPBUTTON_CUBIC_BEZIER_CURVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_cubic_bezier_curveClick);
    Connect(ID_BITMAPBUTTON_SPLINE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_splineClick);
    Connect(ID_BITMAPBUTTON_ENDPOINT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_endpointClick);
    Connect(ID_BITMAPBUTTON_MIDPOINT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_midpointClick);
    Connect(ID_BITMAPBUTTON_PERPENDICULAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_perpendicularClick);
    Connect(ID_BITMAPBUTTON_INTERSECTION,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_intersectionClick);
    Connect(ID_BITMAPBUTTON_NEAREST,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_nearestClick);
    Connect(ID_BITMAPBUTTON_CIRCLECENTER,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_circlecenterClick);
    Connect(ID_BITMAPBUTTON_TANGENT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_tangentClick);
    Connect(ID_BITMAPBUTTON_CIRCLE_4P,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_circle_4pClick);
    Connect(ID_BITMAPBUTTON_GRID,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_gridClick);
    Connect(ID_BITMAPBUTTON_ortho,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_orthoClick);
    Connect(ID_BITMAPBUTTON_MOVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_moveClick);
    Connect(ID_BITMAPBUTTON_COPY,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_copyClick);
    Connect(ID_BITMAPBUTTON_OFFSET,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_offsetClick);
    Connect(ID_BITMAPBUTTON_STRETCH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_stretchClick);
    Connect(ID_BITMAPBUTTON_MIRROR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_mirrorClick);
    Connect(ID_BITMAPBUTTON_ROTATE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_rotateClick);
    Connect(ID_BITMAPBUTTON_SCALE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_scaleClick);
    Connect(ID_BITMAPBUTTON_EXTEND,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_extendClick);
    Connect(ID_BITMAPBUTTON_TRIM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_trimClick);
    Connect(ID_BITMAPBUTTON_FILLED,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_filledClick);
    Connect(ID_BITMAPBUTTON_CHAMFER,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_chamferClick);
    Connect(ID_BITMAPBUTTON_MATCH_PROPERTIES,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_match_propertiesClick);
    Connect(ID_BITMAPBUTTON_DIMENSION_HORIZONTAL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_dimension_horizontalClick);
    Connect(ID_BITMAPBUTTON_DIMENSION_VERTICAL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_dimension_verticalClick);
    Connect(ID_BITMAPBUTTON_DIMENSION_NON_HORIZONTAL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_dimension_non_horizontalClick);
    Connect(ID_BITMAPBUTTON_DIMENSION_DIAMETER,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_dimension_diameterClick);
    Connect(ID_BITMAPBUTTON_DIMENSION_RADIUS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_dimension_radiusClick);
    Connect(ID_BITMAPBUTTON_DIMENSION_ANGLE_2P,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_dimension_angle_2pClick);
    Connect(ID_BITMAPBUTTON_DIMENSION_ANGLE_3P,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_dimension_angle_3pClick);
    Connect(ID_BITMAPBUTTON_DIMENSION_EDIT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_dimension_editClick);
    Connect(ID_BITMAPBUTTON_FILE_NEW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_file_newClick);
    Connect(ID_BITMAPBUTTON_FILE_OPEN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_file_openClick);
    Connect(ID_BITMAPBUTTON_FILE_SAVE_AS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_file_save_asClick);
    Connect(ID_BITMAPBUTTON_PRINT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_printClick);
    Connect(ID_BITMAPBUTTON_VIEW_3D,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_view_3dClick);
    Connect(ID_BITMAPBUTTON_VIEW_TOP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_view_topClick);
    Connect(ID_BITMAPBUTTON_VIEW_BOTTOM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_view_bottomClick);
    Connect(ID_BITMAPBUTTON_VIEW_LEFT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_view_leftClick);
    Connect(ID_BITMAPBUTTON_VIEW_RIGHT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_view_rightClick);
    Connect(ID_BITMAPBUTTON_VIEW_FRONT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_view_frontClick);
    Connect(ID_BITMAPBUTTON_VIEW_BACK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_view_backClick);
    Connect(ID_BITMAPBUTTON_VIEW_EXTEND,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_view_extendClick);
    Connect(ID_BITMAPBUTTON_ZOOM_WINDOW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_zoom_windowClick);
    Connect(ID_BITMAPBUTTON_ZOOM_PLUS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_zoom_plusClick);
    Connect(ID_BITMAPBUTTON_ZOOM_MIN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_zoom_minClick);
    Connect(ID_BITMAPBUTTON_DELETE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_deleteClick);
    Connect(ID_BITMAPBUTTON_CAD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_cadClick);
    Connect(ID_BITMAPBUTTON_CAM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_camClick);
    Connect(ID_BITMAPBUTTON_DEBUG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CadFrame::OnBitmapButton_debugClick);
    //*)

}

CadFrame::~CadFrame()
{
    //(*Destroy(CadFrame)

    //*)
    AuiManager1->UnInit();

}

void CadFrame::OnSpinTimer(wxTimerEvent& event)
{
    wxString x = wxString::Format(wxT("%f"),mouse_cad_pos_x);
    TextCtrl_mouse_pos_x->Clear();
    TextCtrl_mouse_pos_x->AppendText(x);

    wxString y = wxString::Format(wxT("%f"),mouse_cad_pos_y);
    TextCtrl_mouse_pos_y->Clear();
    TextCtrl_mouse_pos_y->AppendText(y);

    TextCtrl_message->Clear();
    TextCtrl_message->AppendText(message);
}

void CadFrame::OnBitmapButton_pointClick(wxCommandEvent& event)
{
    mode = "point";
    message = ">> mode " + mode;
    click=0;
}

void CadFrame::OnBitmapButton_lineClick(wxCommandEvent& event)
{
    mode = "line";
    message = ">> mode " + mode;
    click=0;
}

void CadFrame::OnBitmapButton_linestripClick(wxCommandEvent& event)
{
    mode = "linestrip";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton1_rectangleClick(wxCommandEvent& event)
{
    mode = "rectangle";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_arcClick(wxCommandEvent& event)
{
    mode = "arc";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_circleClick(wxCommandEvent& event)
{
    mode = "circle";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_circle_3pClick(wxCommandEvent& event)
{
    mode = "circle_3p";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_polygonClick(wxCommandEvent& event)
{
    mode = "polygon";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_ellipseClick(wxCommandEvent& event)
{
    mode = "ellipse";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_cubic_bezier_curveClick(wxCommandEvent& event)
{
    mode = "cubic_bezier_curve";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_splineClick(wxCommandEvent& event)
{
    mode = "spline";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_endpointClick(wxCommandEvent& event)
{
    mode_snap = "snap_endpoint";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_midpointClick(wxCommandEvent& event)
{
    mode_snap = "snap_midpoint";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_perpendicularClick(wxCommandEvent& event)
{
    mode_snap = "snap_perpendicular";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_intersectionClick(wxCommandEvent& event)
{
    mode_snap = "snap_intersection";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_nearestClick(wxCommandEvent& event)
{
    mode_snap = "snap_nearest";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_circlecenterClick(wxCommandEvent& event)
{
    mode_snap = "snap_circlecenter";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_tangentClick(wxCommandEvent& event)
{
    mode_snap = "snap_tangent";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_circle_4pClick(wxCommandEvent& event)
{
    mode_snap = "snap_circle_4p";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_gridClick(wxCommandEvent& event)
{
    mode_snap = "grid";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_orthoClick(wxCommandEvent& event)
{
    mode_snap = "ortho";
    message = ">> mode " + mode_snap;
}

void CadFrame::OnBitmapButton_moveClick(wxCommandEvent& event)
{
    mode = "move";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_copyClick(wxCommandEvent& event)
{
    mode = "copy";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_offsetClick(wxCommandEvent& event)
{
    mode = "offset";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_stretchClick(wxCommandEvent& event)
{
    mode = "stretch";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_mirrorClick(wxCommandEvent& event)
{
    mode = "mirror";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_rotateClick(wxCommandEvent& event)
{
    mode = "rotate";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_scaleClick(wxCommandEvent& event)
{
    mode = "scale";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_extendClick(wxCommandEvent& event)
{
    mode = "extend";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_trimClick(wxCommandEvent& event)
{
    mode = "trim";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_filledClick(wxCommandEvent& event)
{
    mode = "filled";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_chamferClick(wxCommandEvent& event)
{
    mode = "chamfer";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_match_propertiesClick(wxCommandEvent& event)
{
    mode = "match_properties";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_dimension_horizontalClick(wxCommandEvent& event)
{
    mode = "dimension_horizontal";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_dimension_verticalClick(wxCommandEvent& event)
{
    mode = "dimension_vertical";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_dimension_non_horizontalClick(wxCommandEvent& event)
{
    mode = "dimension_non_horizontal";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_dimension_diameterClick(wxCommandEvent& event)
{
    mode = "dimension_diameter";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_dimension_radiusClick(wxCommandEvent& event)
{
    mode = "dimension_radius";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_dimension_angle_2pClick(wxCommandEvent& event)
{
    mode = "dimension_angle_2p";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_dimension_angle_3pClick(wxCommandEvent& event)
{
    mode = "dimension_angle_3p";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_dimension_editClick(wxCommandEvent& event)
{
    mode = "dimension_edit";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_file_newClick(wxCommandEvent& event)
{
    //empty cad array
    mode = "file_new";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_file_openClick(wxCommandEvent& event)
{
    //file open dialog
    mode = "file_open";
    message = ">> mode " + mode;

    wxFileDialog* OpenDialog = new wxFileDialog(this, _("Open file"), "", "",
                       "DXF 2013/2014/2015/2016/2017 (*dxf)|*dxf", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    //"  DXF 2013/2014/2015/2016/2017 (*dxf)|*dxf|  DXF LT97/LT98/INKSCAPE (*.dxf)|*.dxf", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    OpenDialog->ShowModal();

    wxFileInputStream input_stream(OpenDialog->GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", OpenDialog->GetPath());
        return;
    }
    int index = OpenDialog->GetFilterIndex();
    read_dxf().LoadFile(OpenDialog->GetPath(),index);

    //message = wxString::Format(wxT("%i"), read_dxf().GetLwPolyLineCount());

}

void CadFrame::OnBitmapButton_file_save_asClick(wxCommandEvent& event)
{
    //file save dialog
    mode = "file_save_as";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_printClick(wxCommandEvent& event)
{
    //print dialog
    mode = "print";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_view_3dClick(wxCommandEvent& event)
{
    mode_view = "view_3d";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_view_topClick(wxCommandEvent& event)
{
    mode_view = "view_top";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_view_bottomClick(wxCommandEvent& event)
{
    mode_view = "view_bottom";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_view_leftClick(wxCommandEvent& event)
{
    mode_view = "view_left";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_view_rightClick(wxCommandEvent& event)
{
    mode_view = "view_right";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_view_frontClick(wxCommandEvent& event)
{
    mode_view = "view_front";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_view_backClick(wxCommandEvent& event)
{
    mode_view = "view_back";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_view_extendClick(wxCommandEvent& event)
{
    mode_view = "zoom_extend";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_zoom_windowClick(wxCommandEvent& event)
{
    mode_view = "zoom_window";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_zoom_plusClick(wxCommandEvent& event)
{
    mode_view = "zoom_plus";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_zoom_minClick(wxCommandEvent& event)
{
    mode_view = "zoom_min";
    message = ">> mode " + mode_view;
}

void CadFrame::OnBitmapButton_deleteClick(wxCommandEvent& event)
{
    mode = "mode_delete";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_debugClick(wxCommandEvent& event)
{
    mode = "mode_debug";
    message = ">> mode " + mode;
    debug_cad_array().cad_array();
}

void CadFrame::OnBitmapButton_camClick(wxCommandEvent& event)
{
    mode = "mode_cam";
    message = ">> mode " + mode;
}

void CadFrame::OnBitmapButton_cadClick(wxCommandEvent& event)
{
    mode = "mode_cad";
    message = ">> mode " + mode;
}











