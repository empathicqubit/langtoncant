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
        *(BYTE*)(0x400+i) = 0x0F; 
    }
}

int isPositionWhite(long x, int y)
{
    
    return 0; // 0 er false...
}

// https://archive.org/details/The_Graphics_Book_for_the_Commodore_64/page/n129/
void setPositionBlack(unsigned short x, BYTE y)
{
    int ra = 320 * (int)(y/8) + (y & 7);
    int ba = 8 * (int)(x/8);
    int ma = 2^(7-(x & 7));
    int sa = 0x2000;
    int ad = sa+ra+ba;
    *(BYTE*)(ad) = *(BYTE*)(ad) | ma;
}

void setPositionWhite(long x, int y)
{
    
}



int main(void) {
    x = 160;
    y = 100;
    printf("%d", direction);
    setAndClearHiRes();
    while (1) {
        setPositionBlack(x,y);
        x = x+1;
        y = y + 1;
    }


    return 0;

}

