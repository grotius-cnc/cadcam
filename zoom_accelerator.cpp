#include "zoom_accelerator.h"
#include <core/variable.h>

zoom_accelerator::zoom_accelerator()
{
        //zoom accelerator..
    if(zoom_cad_right - zoom_cad_left > 5 && zoom_cad_right - zoom_cad_left < 10){
        zoom_cad_factor = 1;

    } else
    if(zoom_cad_right - zoom_cad_left >= 10 && zoom_cad_right - zoom_cad_left < 50){
        zoom_cad_factor = 2;

    } else
    if(zoom_cad_right - zoom_cad_left >= 50 && zoom_cad_right - zoom_cad_left < 100){
        zoom_cad_factor = 4;

    } else
    if(zoom_cad_right - zoom_cad_left >= 100 && zoom_cad_right - zoom_cad_left < 200){
        zoom_cad_factor = 10;

    } else
    if(zoom_cad_right - zoom_cad_left >= 200 && zoom_cad_right - zoom_cad_left < 300){
        zoom_cad_factor = 25;

    } else
    if(zoom_cad_right - zoom_cad_left >= 300 && zoom_cad_right - zoom_cad_left < 400){
        zoom_cad_factor = 50;

    } else
    if(zoom_cad_right - zoom_cad_left >= 400 && zoom_cad_right - zoom_cad_left < 800){
        zoom_cad_factor = 100;

    } else
    if(zoom_cad_right - zoom_cad_left >= 800 && zoom_cad_right - zoom_cad_left < 3000){
        zoom_cad_factor = 200;

    } else
    if(zoom_cad_right - zoom_cad_left >= 3000){
        zoom_cad_factor = 1000;

    }
}
