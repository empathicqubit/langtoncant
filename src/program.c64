#include <stdio.h>
#define BYTE unsigned char

int i;
int main(void) {
    printf("Hello ant");
    while (1) 
    {
        i++;
        *(BYTE*)0xd020 = i;
        *(BYTE*)0xd021 = i+1;
        if (i > 254)
            i = 0;
    }

    return 0;
}