/***************************************************************
 * Name:      CadMain.h
 * Purpose:   Defines Application Frame
 * Author:    coder ()
 * Created:   2020-01-26
 * Copyright: coder ()
 * License:
 **************************************************************/

#ifndef CADMAIN_H
#define CADMAIN_H
#include "opengl.h"
#include <core/variable.h>

//(*Headers(CadFrame)
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
//*)

class CadFrame: public wxFrame
{
    public:

        CadFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~CadFrame();

    private:

        void OnSpinTimer(wxTimerEvent& event);
        wxTimer m_spinTimer;

        //(*Handlers(CadFrame)
        void OnPanel1Paint(wxPaintEvent& event);
        void OnAuiNotebook1PageClose(wxAuiNotebookEvent& event);
        void OnBitmapButton_pointClick(wxCommandEvent& event);
        void OnBitmapButton_lineClick(wxCommandEvent& event);
        void OnBitmapButton_linestripClick(wxCommandEvent& event);
        void OnBitmapButton1_rectangleClick(wxCommandEvent& event);
        void OnBitmapButton_arcClick(wxCommandEvent& event);
        void OnBitmapButton_circleClick(wxCommandEvent& event);
        void OnBitmapButton_circle_3pClick(wxCommandEvent& event);
        void OnBitmapButton_polygonClick(wxCommandEvent& event);
        void OnBitmapButton_ellipseClick(wxCommandEvent& event);
        void OnBitmapButton_cubic_bezier_curveClick(wxCommandEvent& event);
        void OnBitmapButton_endpointClick(wxCommandEvent& event);
        void OnBitmapButton_splineClick(wxCommandEvent& event);
        void OnBitmapButton_midpointClick(wxCommandEvent& event);
        void OnBitmapButton_perpendicularClick(wxCommandEvent& event);
        void OnBitmapButton_nearestClick(wxCommandEvent& event);
        void OnBitmapButton_circlecenterClick(wxCommandEvent& event);
        void OnBitmapButton_tangentClick(wxCommandEvent& event);
        void OnBitmapButton_circle_4pClick(wxCommandEvent& event);
        void OnBitmapButton_gridClick(wxCommandEvent& event);
        void OnBitmapButton_orthoClick(wxCommandEvent& event);
        void OnBitmapButton_moveClick(wxCommandEvent& event);
        void OnBitmapButton_intersectionClick(wxCommandEvent& event);
        void OnBitmapButton_copyClick(wxCommandEvent& event);
        void OnBitmapButton_offsetClick(wxCommandEvent& event);
        void OnBitmapButton_stretchClick(wxCommandEvent& event);
        void OnBitmapButton_mirrorClick(wxCommandEvent& event);
        void OnBitmapButton_rotateClick(wxCommandEvent& event);
        void OnBitmapButton_scaleClick(wxCommandEvent& event);
        void OnBitmapButton_extendClick(wxCommandEvent& event);
        void OnBitmapButton_trimClick(wxCommandEvent& event);
        void OnBitmapButton_filledClick(wxCommandEvent& event);
        void OnBitmapButton_chamferClick(wxCommandEvent& event);
        void OnBitmapButton_match_propertiesClick(wxCommandEvent& event);
        void OnBitmapButton_dimension_horizontalClick(wxCommandEvent& event);
        void OnBitmapButton_dimension_verticalClick(wxCommandEvent& event);
        void OnBitmapButton_dimension_non_horizontalClick(wxCommandEvent& event);
        void OnBitmapButton_dimension_diameterClick(wxCommandEvent& event);
        void OnBitmapButton_dimension_radiusClick(wxCommandEvent& event);
        void OnBitmapButton_dimension_angle_2pClick(wxCommandEvent& event);
        void OnBitmapButton_dimension_angle_3pClick(wxCommandEvent& event);
        void OnBitmapButton_dimension_editClick(wxCommandEvent& event);
        void OnBitmapButton_file_newClick(wxCommandEvent& event);
        void OnBitmapButton_file_openClick(wxCommandEvent& event);
        void OnBitmapButton_file_save_asClick(wxCommandEvent& event);
        void OnBitmapButton_printClick(wxCommandEvent& event);
        void OnBitmapButton_view_3dClick(wxCommandEvent& event);
        void OnBitmapButton_view_topClick(wxCommandEvent& event);
        void OnBitmapButton_view_bottomClick(wxCommandEvent& event);
        void OnBitmapButton_view_leftClick(wxCommandEvent& event);
        void OnBitmapButton_view_rightClick(wxCommandEvent& event);
        void OnBitmapButton_view_frontClick(wxCommandEvent& event);
        void OnBitmapButton_view_backClick(wxCommandEvent& event);
        void OnBitmapButton_view_extendClick(wxCommandEvent& event);
        void OnBitmapButton_zoom_windowClick(wxCommandEvent& event);
        void OnBitmapButton_zoom_plusClick(wxCommandEvent& event);
        void OnBitmapButton_zoom_minClick(wxCommandEvent& event);
        void OnBitmapButton_deleteClick(wxCommandEvent& event);
        void OnBitmapButton_debugClick(wxCommandEvent& event);
        void OnBitmapButton_camClick(wxCommandEvent& event);
        void OnBitmapButton_cadClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(CadFrame)
        static const long ID_PANEL1;
        static const long ID_BITMAPBUTTON_POINT;
        static const long ID_BITMAPBUTTON_LINE;
        static const long ID_BITMAPBUTTON_LINESTRIP;
        static const long ID_BITMAPBUTTON_RECTANGLE;
        static const long ID_BITMAPBUTTON_ARC;
        static const long ID_BITMAPBUTTON_CIRCLE;
        static const long ID_BITMAPBUTTON_CIRCLE_3P;
        static const long ID_BITMAPBUTTON_POLYGON;
        static const long ID_BITMAPBUTTON_ELLIPSE;
        static const long ID_BITMAPBUTTON_CUBIC_BEZIER_CURVE;
        static const long ID_BITMAPBUTTON_SPLINE;
        static const long ID_BITMAPBUTTON_ENDPOINT;
        static const long ID_BITMAPBUTTON_MIDPOINT;
        static const long ID_BITMAPBUTTON_PERPENDICULAR;
        static const long ID_BITMAPBUTTON_INTERSECTION;
        static const long ID_BITMAPBUTTON_NEAREST;
        static const long ID_BITMAPBUTTON_CIRCLECENTER;
        static const long ID_BITMAPBUTTON_TANGENT;
        static const long ID_BITMAPBUTTON_CIRCLE_4P;
        static const long ID_BITMAPBUTTON_GRID;
        static const long ID_BITMAPBUTTON_ortho;
        static const long ID_BITMAPBUTTON_MOVE;
        static const long ID_BITMAPBUTTON_COPY;
        static const long ID_BITMAPBUTTON_OFFSET;
        static const long ID_BITMAPBUTTON_STRETCH;
        static const long ID_BITMAPBUTTON_MIRROR;
        static const long ID_BITMAPBUTTON_ROTATE;
        static const long ID_BITMAPBUTTON_SCALE;
        static const long ID_BITMAPBUTTON_EXTEND;
        static const long ID_BITMAPBUTTON_TRIM;
        static const long ID_BITMAPBUTTON_FILLED;
        static const long ID_BITMAPBUTTON_CHAMFER;
        static const long ID_BITMAPBUTTON_MATCH_PROPERTIES;
        static const long ID_BITMAPBUTTON_DIMENSION_HORIZONTAL;
        static const long ID_BITMAPBUTTON_DIMENSION_VERTICAL;
        static const long ID_BITMAPBUTTON_DIMENSION_NON_HORIZONTAL;
        static const long ID_BITMAPBUTTON_DIMENSION_DIAMETER;
        static const long ID_BITMAPBUTTON_DIMENSION_RADIUS;
        static const long ID_BITMAPBUTTON_DIMENSION_ANGLE_2P;
        static const long ID_BITMAPBUTTON_DIMENSION_ANGLE_3P;
        static const long ID_BITMAPBUTTON_DIMENSION_EDIT;
        static const long ID_PANEL3;
        static const long ID_BITMAPBUTTON_FILE_NEW;
        static const long ID_BITMAPBUTTON_FILE_OPEN;
        static const long ID_BITMAPBUTTON_FILE_SAVE_AS;
        static const long ID_BITMAPBUTTON_PRINT;
        static const long ID_BITMAPBUTTON_VIEW_3D;
        static const long ID_BITMAPBUTTON_VIEW_TOP;
        static const long ID_BITMAPBUTTON_VIEW_BOTTOM;
        static const long ID_BITMAPBUTTON_VIEW_LEFT;
        static const long ID_BITMAPBUTTON_VIEW_RIGHT;
        static const long ID_BITMAPBUTTON_VIEW_FRONT;
        static const long ID_BITMAPBUTTON_VIEW_BACK;
        static const long ID_BITMAPBUTTON_VIEW_EXTEND;
        static const long ID_BITMAPBUTTON_ZOOM_WINDOW;
        static const long ID_BITMAPBUTTON_ZOOM_PLUS;
        static const long ID_BITMAPBUTTON_ZOOM_MIN;
        static const long ID_BITMAPBUTTON_DELETE;
        static const long ID_BITMAPBUTTON4;
        static const long ID_CHOICE2;
        static const long ID_BITMAPBUTTON5;
        static const long ID_CHOICE1;
        static const long ID_BITMAPBUTTON6;
        static const long ID_CHOICE3;
        static const long ID_BITMAPBUTTON60;
        static const long ID_BITMAPBUTTON61;
        static const long ID_PANEL2;
        static const long ID_BITMAPBUTTON_CAD;
        static const long ID_BITMAPBUTTON_CAM;
        static const long ID_BITMAPBUTTON_DEBUG;
        static const long ID_PANEL4;
        static const long ID_TEXTCTRL_message;
        static const long ID_TEXTCTRL_USER_INPUT;
        static const long ID_TEXTCTRL_MOUSE_POS_X;
        static const long ID_TEXTCTRL_MOUSE_POS_Y;
        static const long ID_PANEL5;
        //*)

        //(*Declarations(CadFrame)
        wxBitmapButton* BitmapButton_spline;
        wxBitmapButton* BitmapButton_midpoint;
        wxBitmapButton* BitmapButton_view_left;
        wxBitmapButton* BitmapButton_file_new;
        wxBitmapButton* BitmapButton_dimension_angle_3p;
        wxBitmapButton* BitmapButton_dimension_radius;
        wxBitmapButton* BitmapButton_view_extend;
        wxBitmapButton* BitmapButton_circle_3p;
        wxBitmapButton* BitmapButton_match_properties;
        wxChoice* Choice3;
        wxBitmapButton* BitmapButton_dimension_vertical;
        wxBitmapButton* BitmapButton_view_right;
        wxBitmapButton* BitmapButton_line;
        wxBitmapButton* BitmapButton_scale;
        wxBitmapButton* BitmapButton_stretch;
        wxBitmapButton* BitmapButton_grid;
        wxBitmapButton* BitmapButton_dimension_horizontal;
        wxBitmapButton* BitmapButton_circle;
        wxBitmapButton* BitmapButton_dimension_diameter;
        wxBitmapButton* BitmapButton_dimension_non_horizontal;
        wxBitmapButton* BitmapButton_delete;
        wxBitmapButton* BitmapButton_ortho;
        wxBitmapButton* BitmapButton_linestrip;
        wxBitmapButton* BitmapButton_copy;
        wxBitmapButton* BitmapButton1_rectangle;
        wxBitmapButton* BitmapButton_zoom_window;
        wxBitmapButton* BitmapButton_move;
        wxChoice* Choice2;
        wxBitmapButton* BitmapButton_trim;
        wxBitmapButton* BitmapButton_mirror;
        wxBitmapButton* BitmapButton_filled;
        wxTextCtrl* TextCtrl_mouse_pos_y;
        wxBitmapButton* BitmapButton_ellipse;
        wxBitmapButton* BitmapButton_extend;
        wxPanel* Panel2;
        wxBitmapButton* BitmapButton_polygon;
        wxBitmapButton* BitmapButton_cam;
        wxBitmapButton* BitmapButton61;
        wxBitmapButton* BitmapButton_nearest;
        wxPanel* Panel4;
        wxBitmapButton* BitmapButton_circlecenter;
        opengl* Panel1;
        wxBitmapButton* BitmapButton_dimension_angle_2p;
        wxBitmapButton* BitmapButton_print;
        wxBitmapButton* BitmapButton_view_bottom;
        wxPanel* Panel5;
        wxChoice* Choice1;
        wxTextCtrl* TextCtrl_message;
        wxBitmapButton* BitmapButton5;
        wxBitmapButton* BitmapButton4;
        wxBitmapButton* BitmapButton_debug;
        wxBitmapButton* BitmapButton_arc;
        wxBitmapButton* BitmapButton_cad;
        wxBitmapButton* BitmapButton_perpendicular;
        wxPanel* Panel3;
        wxBitmapButton* BitmapButton_view_3d;
        wxBitmapButton* BitmapButton_dimension_edit;
        wxBitmapButton* BitmapButton_rotate;
        wxBitmapButton* BitmapButton_tangent;
        wxBitmapButton* BitmapButton_endpoint;
        wxTextCtrl* TextCtrl_mouse_pos_x;
        wxBitmapButton* BitmapButton_circle_4p;
        wxBitmapButton* BitmapButton_view_back;
        wxBitmapButton* BitmapButton_file_open;
        wxBitmapButton* BitmapButton_offset;
        wxBitmapButton* BitmapButton_intersection;
        wxBitmapButton* BitmapButton_file_save_as;
        wxBitmapButton* BitmapButton_view_top;
        wxBitmapButton* BitmapButton60;
        wxBitmapButton* BitmapButton_zoom_plus;
        wxBitmapButton* BitmapButton_point;
        wxAuiManager* AuiManager1;
        wxBitmapButton* BitmapButton_chamfer;
        wxBitmapButton* BitmapButton6;
        wxTextCtrl* TextCtrl_user_input;
        wxBitmapButton* BitmapButton_zoom_min;
        wxBitmapButton* BitmapButton_view_front;
        wxBitmapButton* BitmapButton_cubic_bezier_curve;
        //*)

        DECLARE_EVENT_TABLE()

};

#endif // CADMAIN_H


















                                        