#include "debug_cad_array.h"
#include <core/variable.h>
#include <iostream>
#include <string>
using namespace std;

void debug_cad_array::cad_array()
{
    for(unsigned int i=0; i<cad_counter; i++){

        cout << "SCAD --string"                             << endl;
        cout << "SCAD[i][0]=layer           " << SCAD[i][0] << endl;

        cout << "ICAD --int"                                << endl;
        cout << "ICAD[i][0]=id              " << ICAD[i][0] << endl;
        cout << "ICAD[i][1]=flag            " << ICAD[i][1] << endl;
        cout << "ICAD[i][2]=color from dxf  " << ICAD[i][2] << endl;
        cout << "ICAD[i][3]=rgba red        " << ICAD[i][3] << endl;
        cout << "ICAD[i][4]=rgba green      " << ICAD[i][4] << endl;
        cout << "ICAD[i][5]=rgba blue       " << ICAD[i][5] << endl;
        cout << "ICAD[i][6]=rgba alpha      " << ICAD[i][6] << endl;

        cout << "DCAD --double"                             << endl;
        cout << "DCAD[i][0]=x start         " << DCAD[i][0] << endl;
        cout << "DCAD[i][1]=y start         " << DCAD[i][1] << endl;
        cout << "DCAD[i][2]=z start         " << DCAD[i][2] << endl;
        cout << "DCAD[i][3]=x end           " << DCAD[i][3] << endl;
        cout << "DCAD[i][4]=y end           " << DCAD[i][4] << endl;
        cout << "DCAD[i][5]=z end           " << DCAD[i][5] << endl;

        cout << "DCAD[i][6]=x center        " << DCAD[i][6] << endl;
        cout << "DCAD[i][7]=y center        " << DCAD[i][7] << endl;
        cout << "DCAD[i][8]=z center        " << DCAD[i][8] << endl;
        cout << "DCAD[i][9]=radius          " << DCAD[i][9] << endl;
        cout << "DCAD[i][10]=start angle    " << DCAD[i][10] << endl;
        cout << "DCAD[i][11]=end angle      " << DCAD[i][11] << endl;
        cout << "DCAD[i][12]=ellipse ratio  " << DCAD[i][12] << endl;
    }
}


