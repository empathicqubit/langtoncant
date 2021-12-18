#include <stdio.h>
#define BYTE unsigned char

short i;
short x;
BYTE y;
BYTE direction; 
short ad;
short x2;
BYTE y2;
BYTE direction2; 

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
    clearHiRes();
    setHiRes();
}

BYTE isPositionWhite() {
    ad = 0x2000+(320 * (BYTE)(y/8)) + (y & 7)+8 * (BYTE)(x/8);
    return *(short*)(ad) & 1 << ((7-(x & 7)));
}

void setPositionWhite() {
    ad = 0x2000+(320 * (y/8)) + (y & 7)+8 * (x/8);
    *(short*)(ad) = *(short*)(ad) | 1 << ((7-(x & 7)));
}

void setPositionBlack() {
    ad = 0x2000+320 * (y/8) + (y & 7)+8 * (x/8);
    *(short*)(ad) = (*(short*)(ad)) & ~(1 << ((7-(x & 7))));
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
BYTE isPositionWhite2() {
    ad = 0x2000+(320 * (BYTE)(y2/8)) + (y2 & 7)+8 * (BYTE)(x2/8);
    return *(short*)(ad) & 1 << ((7-(x2 & 7)));
}

void setPositionWhite2() {
    ad = 0x2000+(320 * (y2/8)) + (y2 & 7)+8 * (x2/8);
    *(short*)(ad) = *(short*)(ad) | 1 << ((7-(x2 & 7)));
}

void setPositionBlack2() {
    ad = 0x2000+320 * (y2/8) + (y2 & 7)+8 * (x2/8);
    *(short*)(ad) = (*(short*)(ad)) & ~(1 << ((7-(x2 & 7))));
}

void moveForward2() {
    if (direction2 == 0) {
        x2 = x2+1;
    } else if (direction2 == 64) {
        y2 = y2+1;
    } else if (direction2 == 128) {
        x2 = x2-1;
    } else if (direction2 == 192) {
        y2 = y2-1;
    }
}

void makeMove2() {
    if (isPositionWhite2()) {
        direction2 = direction2 - 64;
        setPositionBlack2();
   } else {
        direction2 = direction2 + 64;
        setPositionWhite2();
    }
    moveForward2();
}


int main(void) {
    for (i = 0;i<12;i++) { printf("\n"); }
    printf("Please wait for ant ...\n");
    for (i = 0;i<12;i++) { printf("\n"); }
    setAndClearHiRes();
    x2 = 150;
    y2 = 100;
    direction2 = 192;
    x = 160;
    y = 100;
    direction = 0;
    while(x > 0 && x < 320 && y > 0 && y < 200)
    {
       makeMove();
       makeMove2();
    }
    return 0;
}