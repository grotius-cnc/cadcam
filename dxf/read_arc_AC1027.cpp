#include "read_arc_AC1027.h"
#include <core/variable.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include <to_rgba.h>

void read_arc_AC1027::arc(wxString filename)
{
    bool trigger=0;
    unsigned int layer_line=0;
    unsigned int color_line=0;
    unsigned int x_start_line=0;
    unsigned int y_start_line=0;
    unsigned int z_start_line=0;
    unsigned int radius_line=0;
    unsigned int start_angle_line=0;
    unsigned int end_angle_line=0;

    string stdfilename = std::string(filename.mb_str()); //convert wxstring to std::string
    unsigned int linenumber=0;
    char count[200];
    FILE *file=fopen(stdfilename.c_str(), "r"); //convert std::string to std::char

    while(file && fgets(count, sizeof(count), file)){
        linenumber++;

        if(strstr(count,"ARC")){
            //cout<<"lwline found at:"<<linenumber<< endl;
            trigger=1;
        }

        if(trigger && strstr(count,"  8")){
            //cout<<"8 found at:"<<linenumber<< endl;
            layer_line=linenumber+1;
        }
        if(trigger && linenumber==layer_line){
            //cout<<"layer:"<<count<< endl;
            SCAD[cad_counter][0]=count;
        }

        if(trigger && strstr(count," 62")){
            //cout<<"62 found at:"<<linenumber<< endl;
            color_line=linenumber+1;
        }
        if(trigger && linenumber==color_line){
            //cout<<"color:"<<count<< endl;
            ICAD[cad_counter][2]=stoi(count);
        }

        if(trigger && strstr(count," 10")){
            //cout<<"10 found at:"<<linenumber<< endl;
            x_start_line=linenumber+1;
        }
        if(trigger && linenumber==x_start_line){
            //cout<<"x start:"<<count<< endl;
            ICAD[cad_counter][0]=4; //id arc
            DCAD[cad_counter][6]=stod(count);
        }

        if(trigger && strstr(count," 20")){
            //cout<<"20 found at:"<<linenumber<< endl;
            y_start_line=linenumber+1;
        }
        if(trigger && linenumber==y_start_line){
            //cout<<"y start:"<<count<< endl;
            DCAD[cad_counter][7]=stod(count);
        }

        if(trigger && strstr(count," 30")){
            //cout<<"30 found at:"<<linenumber<< endl;
            z_start_line=linenumber+1;
        }
        if(trigger && linenumber==z_start_line){
            //cout<<"z start:"<<count<< endl;
            DCAD[cad_counter][8]=stod(count);
        }

        if(trigger && strstr(count," 40")){
            //cout<<"11 found at:"<<linenumber<< endl;
            radius_line=linenumber+1;
        }
        if(trigger && linenumber==radius_line){
            //cout<<"x end:"<<count<< endl;
            DCAD[cad_counter][9]=stod(count);
        }

        if(trigger && strstr(count," 50")){
            //cout<<"21 found at:"<<linenumber<< endl;
            start_angle_line=linenumber+1;
        }
        if(trigger && linenumber==start_angle_line){
            //cout<<"y end:"<<count<< endl;
            DCAD[cad_counter][10]=stod(count);
        }

        if(trigger && strstr(count," 51")){
            //cout<<"31 found at:"<<linenumber<< endl;
            end_angle_line=linenumber+1;
        }
        if(trigger && linenumber==end_angle_line){
            //cout<<"z end:"<<count<< endl;
            DCAD[cad_counter][11]=stod(count);
            cad_counter++;
            trigger=0;
        }
    }
}
