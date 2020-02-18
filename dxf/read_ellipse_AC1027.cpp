#include "read_ellipse_AC1027.h"
#include <core/variable.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include <to_rgba.h>
//http://help.autodesk.com/view/ACD/2016/ENU/?guid=GUID-107CB04F-AD4D-4D2F-8EC9-AC90888063AB

void read_ellipse_AC1027::ellipse(wxString filename)
{
    bool trigger=0;
    unsigned int layer_line=0;
    unsigned int color_line=0;
    unsigned int x_center_line=0;
    unsigned int y_center_line=0;
    unsigned int z_center_line=0;
    unsigned int x_endpoint_mayor_axis_line=0;
    unsigned int y_endpoint_mayor_axis_line=0;
    unsigned int z_endpoint_mayor_axis_line=0;
    unsigned int ratio_line=0;
    unsigned int start_angle_line=0;
    unsigned int end_angle_line=0;

    string layer;
    unsigned int color;
    double x_center=0;
    double y_center=0;
    double z_center=0;
    double x_endpoint_mayor=0;
    double y_endpoint_mayor=0;
    double z_endpoint_mayor=0;
    double ratio_=0;
    double start_angle=0;
    double end_angle=0;

    string stdfilename = std::string(filename.mb_str()); //convert wxstring to std::string
    unsigned int linenumber=0;
    char count[200];
    FILE *file=fopen(stdfilename.c_str(), "r"); //convert std::string to std::char

    while(file && fgets(count, sizeof(count), file)){
        linenumber++;

        if(strstr(count,"ELLIPSE")){
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

        if(trigger && strstr(count," 10")){
            //cout<<"10 found at:"<<linenumber<< endl;
            x_center_line=linenumber+1;
        }
        if(trigger && linenumber==x_center_line){
            //cout<<"x start:"<<count<< endl;
            x_center=stod(count);
        }

        if(trigger && strstr(count," 20")){
            //cout<<"20 found at:"<<linenumber<< endl;
            y_center_line=linenumber+1;
        }
        if(trigger && linenumber==y_center_line){
            //cout<<"y start:"<<count<< endl;
            y_center=stod(count);
        }

        if(trigger && strstr(count," 30")){
            //cout<<"30 found at:"<<linenumber<< endl;
            z_center_line=linenumber+1;
        }
        if(trigger && linenumber==z_center_line){
            //cout<<"z start:"<<count<< endl;
            z_center=stod(count);
        }

        if(trigger && strstr(count," 11")){
            //cout<<"10 found at:"<<linenumber<< endl;
            x_endpoint_mayor_axis_line=linenumber+1;
        }
        if(trigger && linenumber==x_endpoint_mayor_axis_line){
            //cout<<"x start:"<<count<< endl;
            x_endpoint_mayor=stod(count);
        }

        if(trigger && strstr(count," 21")){
            //cout<<"20 found at:"<<linenumber<< endl;
            y_endpoint_mayor_axis_line=linenumber+1;
        }
        if(trigger && linenumber==y_endpoint_mayor_axis_line){
            //cout<<"y start:"<<count<< endl;
            y_endpoint_mayor=stod(count);
        }

        if(trigger && strstr(count," 31")){
            //cout<<"30 found at:"<<linenumber<< endl;
            z_endpoint_mayor_axis_line=linenumber+1;
        }
        if(trigger && linenumber==z_endpoint_mayor_axis_line){
            //cout<<"z start:"<<count<< endl;
            z_endpoint_mayor=stod(count);
        }

        if(trigger && strstr(count," 40")){
            //cout<<"30 found at:"<<linenumber<< endl;
            ratio_line=linenumber+1;
        }
        if(trigger && linenumber==ratio_line){
            //cout<<"z start:"<<count<< endl;
            ratio_=stod(count);
        }

        if(trigger && strstr(count," 41")){
            //cout<<"30 found at:"<<linenumber<< endl;
            start_angle_line=linenumber+1;
        }
        if(trigger && linenumber==start_angle_line){
            //cout<<"z start:"<<count<< endl;
            start_angle=stod(count);
        }

        if(trigger && strstr(count," 42")){
            //cout<<"30 found at:"<<linenumber<< endl;
            end_angle_line=linenumber+1;
        }
        if(trigger && linenumber==end_angle_line){
            //cout<<"z start:"<<count<< endl;
            end_angle=stod(count);
        }

        if(trigger && strstr(count,"  0")){
            trigger=0;

            SCAD[cad_counter][0]=layer;
            ICAD[cad_counter][0]=6;     //id ellipse
            ICAD[cad_counter][2]=color;
            DCAD[cad_counter][0]=x_endpoint_mayor; //relative to ellipse centerpoint..
            DCAD[cad_counter][1]=y_endpoint_mayor;
            DCAD[cad_counter][2]=z_endpoint_mayor;

            DCAD[cad_counter][6]=x_center;
            DCAD[cad_counter][7]=y_center;
            DCAD[cad_counter][8]=z_center;

            DCAD[cad_counter][10]=start_angle;
            DCAD[cad_counter][11]=end_angle;
            DCAD[cad_counter][12]=ratio_;

            cad_counter++;
        }

    }
}
