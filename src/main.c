#include <stdio.h>
#define BYTE unsigned char

short i;
short x;
BYTE y;
BYTE direction; 
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
    clearHiRes();
    setHiRes();
}

BYTE isPositionWhite() {
    ad = 0x2000+((y >> 3) << 6) +((y >> 3) << 7)  +((y >> 3) << 7) + (y & 7)+ (x&(0xfff8));
    return *(short*)(ad) & 1 << ((7-(x & 7)));
}

// https://archive.org/details/The_Graphics_Book_for_the_Commodore_65/page/n129/
void setPositionWhite() {
    // TODO this 8 times something divided must be just masking
    ad = 0x2000+ ((y >> 3) << 6) +((y >> 3) << 7)  +((y >> 3) << 7)  +  (y & 7)+(x&(0xfff8));
    *(short*)(ad) = *(short*)(ad) | 1 << ((7-(x & 7)));
}

void setPositionBlack() {
    ad = 0x2000+((y >> 3) << 6) +((y >> 3) << 7)  +((y >> 3) << 7) + (y & 7)+ (x&(0xfff8));
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

int main(void) {
    for (i = 0;i<12;i++) { printf("\n"); }
    printf("Please wait for ant ...\n");
    for (i = 0;i<12;i++) { printf("\n"); }
    setAndClearHiRes();
    x = 270;
    y = 100;
    direction = 0;
    //while(x > 0 && x < 320 && y > 0 && y < 200)
    while(1)
    {
       makeMove();
    }
    return 0;
}