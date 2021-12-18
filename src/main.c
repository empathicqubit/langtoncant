#include <stdio.h>
#define BYTE unsigned char

// bit-mapped graphics memory is located $2000-$3FFF (8192-16383) 
// and that the video RAM lies at $0400-$07FF (1024-2047). 
// This makes it impossible to work with text and graphics at the same time

// The C heap is located at the end of the program and grows towards the C runtime stack.

// https://cc65.github.io/doc/c64.html#ss4.1
// The C runtime stack is located at $CFFF (53247) and growing downwards.
// Should be plenty of stack space between the top of the graphics memory


unsigned short i;
short x; // maybe if the ant does not go tooo far it could be an int..
short y;
short direction; // 0 = right, 64 = up, 128 = left, 192 = down
void setHiRes(void) {
    *(BYTE*)0xd011 = *(BYTE*)0xd011 | 0xb0 ; // Graphics on
    *(BYTE*)0xd016 = *(BYTE*)0xd016 & 240; //Multi color off
    *(BYTE*)0xd018 = *(BYTE*)0xd018 | 8 ; // Graphics to $2000
}
void clearHiRes(void) {
    // Hi-res is turned on by setting bits 5 and 6 (bit 6 must be set in any event) 
    // of register 17 of the VIC and clearing bit 4 of register 22. 
    // Clear memory
    for (i =0;i< 8000; i++)
    {
        *(BYTE*)(0x2000+i) = 0; 
    }

    // Clear colors 
    for (i =0;i< 1000; i++)
    {
        *(BYTE*)(0x400+i) = 0xf0; 
    }
}

void fillHiRes(void) {
    // Hi-res is turned on by setting bits 5 and 6 (bit 6 must be set in any event) 
    // of register 17 of the VIC and clearing bit 4 of register 22. 
    // Clear memory
    for (i =0;i< 8000; i++)
    {
        *(BYTE*)(0x2000+i) = 0xff; 
    }
}


void setAndClearHiRes(){
    setHiRes();
    clearHiRes();
}

// need to think
BYTE isPositionWhite(short x, short y)
{
    short ra = (320 * (short)(y/8)) + (y & 7);
    short ba = 8 * (short)(x/8);
    short ma = 1 << ((7-(x & 7)));
    short sa = 0x2000;
    short ad = sa+ra+ba;
    return *(short*)(ad) & ma;
}


// https://archive.org/details/The_Graphics_Book_for_the_Commodore_64/page/n129/
void setPositionWhite(short x, short y)
{
    short ra = (320 * (short)(y/8)) + (y & 7);
    short ba = 8 * (short)(x/8);
    short ma = 1 << ((7-(x & 7)));
    short sa = 0x2000;
    short ad = sa+ra+ba;
    *(short*)(ad) = *(short*)(ad) | ma;
}

void setPositionBlack(unsigned short x, unsigned short y)
{
    short ra = (320 * (short)(y/8)) + (y & 7);
    short ba = 8 * (short)(x/8);
    short ma = (1 << ((7-(x & 7))));
    short sa = 0x2000;
    short ad = sa+ra+ba;
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

void turnLeft(){
    direction = direction + 64;
    if (direction >= 255) 
        direction = 0;
}

void turnRight(){
    direction = direction - 64;
    if (direction <0) 
        direction = 192;
}


void makeMove() {
    if (isPositionWhite(x,y)) {
        turnRight();
        setPositionBlack(x,y);
   } else {
        turnLeft(); 
        setPositionWhite(x,y);
    }
    moveForward();
}

unsigned short line;
unsigned short foo; 
unsigned short j; 
int main(void) {

    setAndClearHiRes();
    for (i = 0;i<50;i++){
        for (j= 0;j<50;j++){
            setPositionWhite(i,j);
        }
    }
     for (i = 0;i<50;i++){
        for (j= 0;j<50;j++){
            setPositionBlack(i,j);
        }
    }
    x = 160;
    y = 100;
    direction = 0;
    while(1)
    {
       makeMove();
    }

    return 0;

}

