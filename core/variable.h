#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>

using namespace std;
extern string mode;
extern string mode_snap;
extern string mode_view;
extern string message;

extern int click;

extern int mouse_pixel_pos_x;
extern int mouse_pixel_pos_y;
extern int screen_pixel_width;
extern int screen_pixel_height;
extern double aspect;

extern double zoom_cad;
extern double zoom_cad_factor;
extern double zoom_cad_left;
extern double zoom_cad_right;
extern double zoom_cad_bottom;
extern double zoom_cad_top;

extern double screen_cad_width;
extern double screen_cad_height;

extern double mouse_cad_pos_x;
extern double mouse_cad_pos_y;

extern double snapshot_cad_mousepos_x;
extern double snapshot_cad_mousepos_y;

extern int delta;

extern unsigned int cad_counter;
extern string SCAD[100000][5];
extern int ICAD[100000][25];
extern double DCAD[100000][75];

class variable
{
    public:
        variable();

    protected:

    private:
};

#endif // VARIABLE_H
