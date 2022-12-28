


#include <stdio.h>
#include <stdlib.h>

#define reg_0 0x43c00000

int main(int argc, char **argv)
{
    int *reg = (int *)(reg_0);
    int data, prv = 0;

    // Repeatly print the register value
    while(1){
        data = *reg;
        if(data != prv){
            printf("%d\n", data);
            prv = data;
        }
    }
    
    return 0;
}
