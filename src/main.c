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
unsigned short x; // maybe if the ant does not go tooo far it could be an int..
BYTE y;
BYTE direction; // 0 = right, 64 = up, 128 = left, 192 = down
void setAndClearHiRes(void) {
    // Hi-res is turned on by setting bits 5 and 6 (bit 6 must be set in any event) 
    // of register 17 of the VIC and clearing bit 4 of register 22. 

    
    *(BYTE*)0xd011 = *(BYTE*)0xd011 | 0xb0 ; // Graphics on
    *(BYTE*)0xd016 = *(BYTE*)0xd016 & 240; //Multi color off
    *(BYTE*)0xd018 = *(BYTE*)0xd018 | 8 ; // Graphics to $2000

    // Clear memory
    for (i =0;i< 8000; i++)
    {
        *(BYTE*)(0x2000+i) = 0; 
    }

    // Clear colors 
    for (i =0;i< 1000; i++)
    {
        *(BYTE*)(0x400+i) = 0xF0; 
    }
}

int isPositionWhite(long x, int y)
{
    
    return 0; // 0 er false...
}

int power(int base, int exponent)
{
    int result=1;
    for (exponent; exponent>0; exponent--)
    {
        result = result * base;
    }
    return result;
}

// https://archive.org/details/The_Graphics_Book_for_the_Commodore_64/page/n129/
void setPositionWhite(unsigned short x, BYTE y)
{
    unsigned short ra = (320 * (BYTE)(y/8)) + (y & 7);
    unsigned short ba = 8 * (BYTE)(x/8);
    unsigned short ma = power(2,(7-(x & 7)));
    unsigned short sa = 0x2000;
    unsigned short ad = sa+ra+ba;
    *(unsigned short*)(ad) = *(unsigned short*)(ad) | ma;
}

void setPositionBlack(unsigned short x, BYTE y)
{
    unsigned short ra = (320 * (BYTE)(y/8)) + (y & 7);
    unsigned short ba = 8 * (BYTE)(x/8);
    unsigned short ma = 255 - power(2,(7-(x & 7)));
    unsigned short sa = 0x2000;
    unsigned short ad = sa+ra+ba;
    *(unsigned short*)(ad) = *(unsigned short*)(ad) & ma;
   
}



unsigned short line;
int main(void) {
    x = 160;
    y = 100;
    setAndClearHiRes();
    for (line = 0;line<50;line++)
    {
        setPositionWhite(x,y);
        x = x+1;
        y = y + 1;
    }

    x = 160;
    y = 100;
    setAndClearHiRes();
    for (line = 0;line<50;line++)
    {
        setPositionBlack(x,y);
        x = x+1;
        y = y + 1;
    }



    return 0;

}

