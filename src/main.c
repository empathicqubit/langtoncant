#define BYTE unsigned char

short i;
short x;
BYTE y;
BYTE direction; 
short ra;
BYTE ba;
BYTE ma;
short sa;
short ad;

void setHiRes() {
    *(BYTE*)0xd011 = *(BYTE*)0xd011 | 0xb0 ; // Graphics on
    *(BYTE*)0xd016 = *(BYTE*)0xd016 & 240; //Multi color off
    *(BYTE*)0xd018 = *(BYTE*)0xd018 | 8 ; // Graphics to $2000
}
void clearHiRes() {
    for (i =0;i< 8000; i++)
    {
        *(BYTE*)(0x2000+i) = 0; 
    }

    for (i =0;i< 1000; i++)
    {
        *(BYTE*)(0x400+i) = 0xf0; 
    }
}

void setAndClearHiRes(){
    setHiRes();
    clearHiRes();
}

BYTE isPositionWhite() {
    ra = (320 * (BYTE)(y/8)) + (y & 7);
    ba = 8 * (BYTE)(x/8);
    ma = 1 << ((7-(x & 7)));
    sa = 0x2000;
    ad = sa+ra+ba;
    return *(BYTE*)(ad) & ma;
}

// https://archive.org/details/The_Graphics_Book_for_the_Commodore_64/page/n129/
void setPositionWhite() {
    ra = (320 * (y/8)) + (y & 7);
    ba = 8 * (short)(x/8);
    ma = 1 << ((7-(x & 7)));
    sa = 0x2000;
    ad = sa+ra+ba;
    *(short*)(ad) = *(short*)(ad) | ma;
}

void setPositionBlack() {
    ra = 320 * (y/8) + (y & 7);
    ba = 8 * (short)(x/8);
    ma = (1 << ((7-(x & 7))));
    sa = 0x2000;
    ad = sa+ra+ba;
    *(short*)(ad) = (*(short*)(ad)) & ~ma;
}

void moveForward() {
    if (direction == 0) {
        x = x+1;
    } else if (direction == 64) {
        y = y+1;
    } else if (direction == 128) {
        x = x-1;
    } else if (direction == 192) {
        y = y-1;
    }
}

void makeMove() {
    if (isPositionWhite()) {
        direction = direction - 64;
        setPositionBlack();
   } else {
        direction = direction + 64;
        setPositionWhite();
    }
    moveForward();
}

int main(void) {
    setAndClearHiRes();
    x = 160;
    y = 100;
    direction = 0;
    while(x > 0 && x < 320 && y > 0 && y < 200)
    {
       makeMove();
    }
    return 0;
}