#include "variable.h"

using namespace std;

string mode;
string mode_snap;
string mode_view;
string message;

int click;
int mouse_pixel_pos_x;
int mouse_pixel_pos_y;
int screen_pixel_width;
int screen_pixel_height;
double aspect;

double zoom_cad;
double zoom_cad_factor = 50;
double zoom_cad_left = -500;
double zoom_cad_right = 500;
double zoom_cad_bottom = -500;
double zoom_cad_top = 500;

double screen_cad_width;
double screen_cad_height;

double mouse_cad_pos_x;
double mouse_cad_pos_y;

double snapshot_cad_mousepos_x;
double snapshot_cad_mousepos_y;

int delta;

unsigned int cad_counter;
string SCAD[100000][5];
int ICAD[100000][25];
double DCAD[100000][75];

variable::variable()
{
    //ctor

}
