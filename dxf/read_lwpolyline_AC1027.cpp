#include "read_lwpolyline_AC1027.h"
#include <core/variable.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
#include <to_rgba.h>


void read_lwpolyline_AC1027::lwpolyline(wxString filename)
{
    bool trigger=0;
    unsigned int layer_line=0;
    unsigned int color_line=0;
    unsigned int x_start_line=0;
    unsigned int y_start_line=0;
    vector<double> x;
    vector<double> y;
    vector<int> color;
    vector<string> layer;

    string stdfilename = std::string(filename.mb_str()); //convert wxstring to std::string
    unsigned int linenumber=0;
    char count[200];
    FILE *file=fopen(stdfilename.c_str(), "r"); //convert std::string to std::char

    while(file && fgets(count, sizeof(count), file)){
        linenumber++;

        if(strstr(count,"LWPOLYLINE")){
            //cout<<"LWPOLYLINE BEGIN:"<<linenumber<< endl;
            trigger=1;
        }

        if(trigger && strstr(count,"  8")){
            //cout<<"8 found at:"<<linenumber<< endl;
            layer_line=linenumber+1;
        }
        if(trigger && linenumber==layer_line){
            //cout<<"layer:"<<count<< endl;
            layer.push_back(count);
        }

        if(trigger && strstr(count," 62")){
            //cout<<"62 found at:"<<linenumber<< endl;
            color_line=linenumber+1;
        }
        if(trigger && linenumber==color_line){
            //cout<<"color:"<<count<< endl;
            color.push_back(stoi(count));
        }

        if(trigger && strstr(count," 10")){
            //cout<<"10 found at:"<<linenumber<< endl;
            x_start_line=linenumber+1;
        }
        if(trigger && linenumber==x_start_line){
            //cout<<"x start:"<<count<< endl;
            x.push_back(stod(count));
        }

        if(trigger && strstr(count," 20")){
            //cout<<"20 found at:"<<linenumber<< endl;
            y_start_line=linenumber+1;
        }
        if(trigger && linenumber==y_start_line){
            //cout<<"y start:"<<count<< endl;
            y.push_back(stod(count));
        }

        if(trigger && strstr(count,"  0")){
            //cout<<"LWPOLYLINE END:"<<linenumber<< endl;
            trigger=0;

            for(int i=0; i!=x.size(); i++){

                if(i>=1){
                    SCAD[cad_counter][0]=layer.at(i);
                    ICAD[cad_counter][0]=2;//id polyline
                    ICAD[cad_counter][2]=color.at(i);//color
                    DCAD[cad_counter][0]=x.at(i-1);
                    DCAD[cad_counter][1]=y.at(i-1);
                    DCAD[cad_counter][3]=x.at(i);
                    DCAD[cad_counter][4]=y.at(i);
                    cad_counter++;
                    //cout<<"x at i-1:"<<x.at(i-1)<< endl;
                    //cout<<"x at i:  "<<x.at(i)<< endl;
                }
            }
            x.clear();
            y.clear();
        }
    }
    fclose(file);
}













