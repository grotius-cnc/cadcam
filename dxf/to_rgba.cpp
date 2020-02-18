#include "to_rgba.h"
#include <core/variable.h>

void to_rgba::rgba(unsigned int i, unsigned int color)
{
    if(color == 1){ //red
        ICAD[i][3] = 255; //red
        ICAD[i][4] = 0; //green
        ICAD[i][5] = 0; //blue
        ICAD[i][6] = 255; //alpha
    }
    if(color == 2){ //yellow
        ICAD[i][3] = 255; //red
        ICAD[i][4] = 255; //green
        ICAD[i][5] = 0; //blue
        ICAD[i][6] = 255; //alpha
    }
    if(color == 3){ //green
        ICAD[i][3] = 0; //red
        ICAD[i][4] = 255; //green
        ICAD[i][5] = 0; //blue
        ICAD[i][6] = 255; //alpha
    }
    if(color == 4){ //cyan
        ICAD[i][3] = 255; //red
        ICAD[i][4] = 0; //green
        ICAD[i][5] = 255; //blue
        ICAD[i][6] = 255; //alpha
    }
    if(color == 5){ //blue
        ICAD[i][3] = 49; //red
        ICAD[i][4] = 112; //green
        ICAD[i][5] = 206; //blue
        ICAD[i][6] = 255; //alpha
    }
    if(color == 6){ //magenta
        ICAD[i][3] = 0; //red
        ICAD[i][4] = 255; //green
        ICAD[i][5] = 255; //blue
        ICAD[i][6] = 255; //alpha
    }
    if(color == 7){ //white
        ICAD[i][3] = 255; //red
        ICAD[i][4] = 255; //green
        ICAD[i][5] = 255; //blue
        ICAD[i][6] = 255; //alpha
    }
    if(color == 8){ //grey
        ICAD[i][3] = 106; //red
        ICAD[i][4] = 106; //green
        ICAD[i][5] = 106; //blue
        ICAD[i][6] = 255; //alpha
    }
    if(color == 9){ //orange/brown
        ICAD[i][3] = 255; //red
        ICAD[i][4] = 170; //green
        ICAD[i][5] = 0; //blue
        ICAD[i][6] = 255; //alpha
    }
}

