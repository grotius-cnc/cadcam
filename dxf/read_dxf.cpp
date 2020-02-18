#include "read_dxf.h"
#include <core/variable.h>
#include <wx/string.h>
#include <iostream>
using namespace std;

#include <read_spline_AC1014.h>
#include <read_line_AC1014.h>

#include <read_line_AC1027.h>
#include <read_circle_AC1027.h>
#include <read_lwpolyline_AC1027.h>
#include <read_arc_AC1027.h>
#include <read_spline_AC1027.h>
#include <read_ellipse_AC1027.h>
/*
Open the DXF file in Notepad and look at the 2nd line under $ACADVER at the top of the file
MC0.0 - DWG Release 1.1
AC1.2 - DWG Release 1.2
AC1.4 - DWG Release 1.4
AC1.50 - DWG Release 2.0
AC2.10 - DWG Release 2.10
AC1002 - DWG Release 2.5
AC1003 - DWG Release 2.6
AC1004 - DWG Release 9
AC1006 - DWG Release 10
AC1009 - DWG Release 11/12 (LT R1/R2)
AC1012 - DWG Release 13 (LT95)
AC1014 - DWG Release 14, 14.01 (LT97/LT98) INKSCAPE
AC1015 - DWG AutoCAD 2000/2000i/2002
AC1018 - DWG AutoCAD 2004/2005/2006
AC1021 - DWG AutoCAD 2007/2008/2009
AC1024 - DWG AutoCAD 2010/2011/2012
AC1027 - DWG AutoCAD 2013/2014/2015/2016/2017
AC1032 - DWG AutoCAD 2018/2019/2020
*/

void read_dxf::LoadFile(wxString filename, int index)
{
    //to keep it structurized the "file read in" is splitted up into several classes..
    if(index==0){
        read_line_AC1027().line(filename);
        read_lwpolyline_AC1027().lwpolyline(filename);
        read_circle_AC1027().circle(filename);
        read_arc_AC1027().arc(filename);
        read_spline_AC1027().spline(filename);
        read_ellipse_AC1027().ellipse(filename);
    }

    /*if(index == 1){
        read_spline_AC1014().spline(filename);
        read_line_AC1014().line(filename);
    }*/
}



















