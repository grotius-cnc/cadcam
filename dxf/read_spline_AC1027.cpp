#include "read_spline_AC1027.h"
#include <core/variable.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include <to_rgba.h>

void read_spline_AC1027::spline(wxString filename)
{
 bool trigger=0;
    unsigned int layer_line=0;
    unsigned int color_line=0;
    unsigned int x_line=0;
    unsigned int y_line=0;
    unsigned int z_line=0;
    string layer;
    unsigned int color = 0;
    double x=0;
    double y=0;
    double z=0;

    string stdfilename = std::string(filename.mb_str()); //convert wxstring to std::string
    unsigned int linenumber=0;
    char count[200];
    FILE *file=fopen(stdfilename.c_str(), "r"); //convert std::string to std::char

    while(file && fgets(count, sizeof(count), file)){
        linenumber++;

        if(strstr(count,"SPLINE")){
            //cout<<"lwline found at:"<<linenumber<< endl;
            trigger=1;
        }

        if(trigger && strstr(count,"  8")){
            //cout<<"8 found at:"<<linenumber<< endl;
            layer_line=linenumber+1;
        }
        if(trigger && linenumber==layer_line){
            //cout<<"layer:"<<count<< endl;
            layer=count;
        }

        if(trigger && strstr(count," 62")){
            //cout<<"62 found at:"<<linenumber<< endl;
            color_line=linenumber+1;
        }
        if(trigger && linenumber==color_line){
            //cout<<"color:"<<count<< endl;
            color=stoi(count);
        }

        if(trigger && strstr(count," 11")){
            //cout<<"10 found at:"<<linenumber<< endl;
            x_line=linenumber+1;
        }
        if(trigger && linenumber==x_line){
            //cout<<"x start:"<<count<< endl;
            x=stod(count);
        }

        if(trigger && strstr(count," 21")){
            //cout<<"20 found at:"<<linenumber<< endl;
            y_line=linenumber+1;
        }
        if(trigger && linenumber==y_line){
            //cout<<"y start:"<<count<< endl;
            y=stod(count);
        }

        if(trigger && strstr(count," 31")){
            //cout<<"30 found at:"<<linenumber<< endl;
            z_line=linenumber+1;
        }
        if(trigger && linenumber==z_line){
            //cout<<"z start:"<<count<< endl;
            z=stod(count);

            SCAD[cad_counter][0]=layer;
            ICAD[cad_counter][0]=5;     //id spline
            ICAD[cad_counter][2]=color;
            //to_rgba().rgba(cad_counter,color);
            DCAD[cad_counter][0]=x;
            DCAD[cad_counter][1]=y;
            DCAD[cad_counter][2]=z;
            cad_counter++;
        }

        if(trigger && strstr(count,"  0")){
            trigger=0;
            ICAD[cad_counter-1][1]=1; //id=flag spline end
        }

    }
}















