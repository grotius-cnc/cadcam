#include "opengl.h"
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <CadMain.h>
#include <core/variable.h>
#include <zoom_accelerator.h>

#define STB_IMAGE_IMPLEMENTATION
#include <wx/filefn.h>

#include <dxf/read_dxf.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
vector<vector<double>> C; //2d array

GLuint LoadBMP(const char *fileName);

enum
{
    ID_TEST_TIMER
};

BEGIN_EVENT_TABLE(opengl, wxGLCanvas)
    EVT_SIZE(opengl::OnSize)
    EVT_LEFT_DOWN(opengl::OnLeftMouse)
    EVT_LEFT_UP(opengl::OnLeftMouseUp)
    EVT_RIGHT_DOWN(opengl::OnRightMouse)
    EVT_RIGHT_UP(opengl::OnRightMouseUp)
    EVT_MIDDLE_DOWN(opengl::OnMiddleMouse)
    EVT_MIDDLE_UP(opengl::OnMiddleMouseUp)
    EVT_MOUSEWHEEL(opengl::OnMiddleMouseWheel)
    EVT_MOTION(opengl::OnMouseMove)
    EVT_TIMER(ID_TEST_TIMER, opengl::ontimer)
END_EVENT_TABLE()

opengl::opengl(wxWindow* parent,
               wxWindowID id,
               const wxPoint& pos,
               const wxSize& size,
               long style,
               const wxString& name,
               int* attribList,
               const wxPalette& palette)
    : wxGLCanvas(parent, id, pos, size, style, name), m_timer(this, ID_TEST_TIMER)
{
    InitGL();
    int w, h;
    GetClientSize(&w, &h);

    m_timer.Start(100);
}

opengl::~opengl()
{
    m_timer.Stop();
}

void opengl::ontimer(wxTimerEvent& event)
{
    update();
}

void opengl::InitGL()
{
    //texture
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    //normal
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_STIPPLE);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 1);
    glLineWidth(1);

    zoom_cad_factor = 50;
    zoom_cad_left = -500;
    zoom_cad_right = 500;
    zoom_cad_bottom = -500;
    zoom_cad_top = 500;
}

void opengl::update()
{
    SetCurrent();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(zoom_cad_left, zoom_cad_right, zoom_cad_bottom/aspect, zoom_cad_top/aspect, -100000.0, 100000.0);

    glTranslated(0.0, 0.0, Depth);
    glRotatef(RotX, 1.0, 0.0, 0.0);
    glRotatef(RotY, 0.0, 1.0, 0.0);

    /*wxString path = wxGetCwd();
    texture = LoadBMP(path + "/bitmap/test.bmp");
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i(0, 0);
    	glTexCoord2i(0, 1); glVertex2i(0, 64);
    	glTexCoord2i(1, 1); glVertex2i(64, 64);
    	glTexCoord2i(1, 0); glVertex2i(64, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);*/

    int segments = 25;
    for(unsigned int i = 0; i < cad_counter; i++)
    {
        if(ICAD[i][0]==1 || ICAD[i][0]==2) //id=line id=polyline
        {
            glBegin(GL_LINES);
            glVertex3d(DCAD[i][0], DCAD[i][1], DCAD[i][2]);
            glVertex3d(DCAD[i][3], DCAD[i][4], DCAD[i][5]);
            glEnd();
        }

        if(ICAD[i][0]==3)//id=circle
        {
            glBegin(GL_LINE_LOOP);
            for (int ii = 0; ii < segments; ii++)
            {
                double theta = 2.0 * M_PI * int(ii) / int(segments );
                double x = DCAD[i][9] * cosf(theta);
                double y = DCAD[i][9] * sinf(theta);
                glVertex3d(x + DCAD[i][6], y + DCAD[i][7], DCAD[i][8]);
            }
            glEnd();
        }

        if(ICAD[i][0]==4)//id=arc
        {
            double angle_start = (DCAD[i][10]/360)*(2*M_PI); //start angle
            if(DCAD[i][11]==360){DCAD[i][11]=0;} //autocad degree problem..
            double angle_end = (DCAD[i][11]/360)*(2*M_PI);

            if (angle_end < angle_start){  //this to avoid the start angle is bigger then the end angle value
                angle_end += 2*M_PI;
            }

            float arc_angle = angle_end - angle_start;
            float theta = arc_angle / float(segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
            float tangetial_factor = tanf(theta);
            float radial_factor = cosf(theta);
            float x = DCAD[i][9] * cosf(angle_start);//we now start at the start angle
            float y = DCAD[i][9] * sinf(angle_start);

            glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
            for(int ii = 0; ii < segments; ii++)
            {
                glVertex2f(x + DCAD[i][6], y + DCAD[i][7]); //x center, y center..

                float tx = -y;
                float ty = x;

                x += tx * tangetial_factor;
                y += ty * tangetial_factor;

                x *= radial_factor;
                y *= radial_factor;
            }
            glEnd();
        }
    }

    for(int i = 0; i < cad_counter; i++)
    {

        if(ICAD[i][0]==5)//id=spline
        {
            C.push_back({DCAD[i][0],DCAD[i][1]});
        }

        if(ICAD[i][0]==5 && ICAD[i][1]==1)//id=spline id=spline end
        {

            double S[C.size()-1][2][4];
            double w, b[C.size()], d[C.size()], x[C.size()];
            int i, dim;
            int n = C.size()-1; // number of splines

            for(dim=0; dim<2; dim++)
            {
                // define d[]:
                d[0]=3.0*(C[1][dim]-C[0][dim]);
                for(i=1; i<n; i++)
                    d[i]=3.0*(C[i+1][dim]-C[i-1][dim]);
                d[n]=3.0*(C[n][dim]-C[n-1][dim]);
                // forward sweep: (simplified tridiagonal solution: all a[i]=1 and all c[i]=1)
                b[0]=2.0;
                for(i=1; i<C.size(); i++)
                {
                    w = 1.0/b[i-1];
                    b[i] = 4.0 - w;
                    d[i] -= (w*d[i-1]);
                }
                // calculate solution vector x[i] = D[i]:
                // (Wikipedia x[] = Wolfram D[])
                x[n]=d[n]/b[n];
                for(i=n-1; i>=0; i--)
                    x[i]=(d[i]-x[i+1])/b[i];
                // calculate spline S[i][dim] a, b, c and d:
                for(i=0; i<n; i++)
                {
                    S[i][dim][0]=C[i][dim];
                    S[i][dim][1]=x[i];
                    S[i][dim][2]=3.0*(C[i+1][dim]-C[i][dim]) - 2.0*x[i] - x[i+1];
                    S[i][dim][3]=2.0*(C[i][dim]-C[i+1][dim]) + x[i] + x[i+1];
                }
            }

            glLineWidth(1);
            glBegin(GL_LINE_STRIP);
            for(int p=0; p<C.size()-1; p++)  //spline points
            {
                for(double t=0; t<1; t+=0.01)  //time 0-1 for each spline
                {
                    double px = ((S[p][0][3]*t+S[p][0][2])*t+S[p][0][1])*t+S[p][0][0];
                    double py = ((S[p][1][3]*t+S[p][1][2])*t+S[p][1][1])*t+S[p][1][0];
                    //std::cout<< "x:" << px << " y:" << py << std::endl;
                    glVertex2d(px,py);
                }
            }
            glEnd();

            /*glPointSize(2);
            glBegin(GL_POINTS);
            for(int i=0; i<=C.size()-1; i++)  //spline points
            {
                    glVertex2d(C[i][0],C[i][1]);

            }
            glEnd();*/

            C.clear(); //empty 2d array
        }
    }

    glFlush();
    SwapBuffers();
}

GLuint LoadBMP(const char *fileName)
{
    FILE *file;
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int size;
    unsigned int width, height;
    unsigned char *data;


    file = fopen(fileName, "rb");

    if (file == NULL)
    {
        wxMessageBox("Error: Invaild file path!");
        return false;
    }

    if (fread(header, 1, 54, file) != 54)
    {
        //MessageBox(NULL, L"Error: Invaild file!", L"Error", MB_OK);
        return false;
    }

    if (header[0] != 'B' || header[1] != 'M')
    {
        //MessageBox(NULL, L"Error: Invaild file!", L"Error", MB_OK);
        return false;
    }

    dataPos		= *(int*)&(header[0x0A]);
    size		= *(int*)&(header[0x22]);
    width		= *(int*)&(header[0x12]);
    height		= *(int*)&(header[0x16]);

    if (size == NULL)
        size = width * height * 3;
    if (dataPos == NULL)
        dataPos = 54;

    data = new unsigned char[size];

    fread(data, 1, size, file);

    fclose(file);

    //LoadBMP:
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    return texture;
}

void opengl::OnSize(wxSizeEvent& event)
{
    // This is necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

    int w, h;
    GetClientSize(&w, &h);
    glViewport(0, 0, w, h);
    screen_pixel_width = double(w);
    screen_pixel_height = double(h);
    aspect = double(w) / double(h);
    screen_cad_width = zoom_cad_right - zoom_cad_left;
    screen_cad_height = (zoom_cad_top - zoom_cad_bottom)/aspect;
}

void opengl::OnLeftMouse(wxMouseEvent& event)
{
    MouseButton = 1;
    event.GetPosition(&Xcoord, &Ycoord);
    click ++;
}

void opengl::OnRightMouse(wxMouseEvent& event)
{
    MouseButton = 2;
    event.GetPosition(&Dummy, &Zcoord);
}

void opengl::OnLeftMouseUp(wxMouseEvent& event)
{
    MouseButton = 0;
}

void opengl::OnRightMouseUp(wxMouseEvent& event)
{
    MouseButton = 0;
}

void opengl::OnMiddleMouse(wxMouseEvent& event)
{
    MouseButton = 3;
    snapshot_cad_mousepos_x = mouse_cad_pos_x;
    snapshot_cad_mousepos_y = mouse_cad_pos_y;
}

void opengl::OnMiddleMouseUp(wxMouseEvent& event)
{
    MouseButton = 0;
}

void opengl::OnMiddleMouseWheel(wxMouseEvent& event)
{
    if(event.GetWheelRotation()>0 && (zoom_cad_right - zoom_cad_left > 5 && zoom_cad_top - zoom_cad_bottom > 5))  //prevent zooming trough the plane.
    {
        zoom_accelerator();
        zoom_cad = zoom_cad + zoom_cad_factor;
        zoom_cad_left = zoom_cad_left + zoom_cad_factor;
        zoom_cad_right = zoom_cad_right - zoom_cad_factor;
        zoom_cad_top = zoom_cad_top - zoom_cad_factor;
        zoom_cad_bottom = zoom_cad_bottom + zoom_cad_factor;
    }
    if(event.GetWheelRotation()<0)  //zoom out
    {
        zoom_accelerator();
        zoom_cad = zoom_cad - zoom_cad_factor;
        zoom_cad_left = zoom_cad_left - zoom_cad_factor;
        zoom_cad_right = zoom_cad_right + zoom_cad_factor;
        zoom_cad_top = zoom_cad_top + zoom_cad_factor;
        zoom_cad_bottom = zoom_cad_bottom - zoom_cad_factor;
    }
}

void opengl::OnMouseMove(wxMouseEvent& event)
{
    event.GetPosition(&X, &Y);
    mouse_pixel_pos_x = X;
    mouse_pixel_pos_y = screen_pixel_height-Y;

    screen_cad_width = double(zoom_cad_right) - double(zoom_cad_left);
    screen_cad_height = (double(zoom_cad_top) - double(zoom_cad_bottom))/aspect;

    mouse_cad_pos_x = (double(mouse_pixel_pos_x) / double(screen_pixel_width)) * screen_cad_width + double(zoom_cad_left);
    mouse_cad_pos_y = ((double(mouse_pixel_pos_y) / double(screen_pixel_height)) * screen_cad_height) + (double(zoom_cad_bottom)/aspect);

    if (event.Dragging() == true)
    {
        event.GetPosition(&X, &Y);
        if (MouseButton == 1)
        {
            RotX=RotX + (GLfloat)(Y - Ycoord)/2;
            RotY=RotY + (GLfloat)(X - Xcoord)/2;
            Xcoord = X;
            Ycoord = Y;
        }
        if (MouseButton == 2)
        {
            Depth = Depth - (GLfloat)(Y-Zcoord)/5;
            Zcoord = Y;
        }
        if (MouseButton == 3)
        {
            double dx = snapshot_cad_mousepos_x - mouse_cad_pos_x;
            double dy = snapshot_cad_mousepos_y - mouse_cad_pos_y;

            zoom_cad_left = zoom_cad_left + dx;
            zoom_cad_right = zoom_cad_right + dx;
            zoom_cad_top = zoom_cad_top + dy;
            zoom_cad_bottom = zoom_cad_bottom + dy;
        }
    }
}















