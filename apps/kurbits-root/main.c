#include <sel4/sel4.h>
#include <stdio.h> //printf
#include <sel4platsupport/io.h> //printf
#include <bcm2835-armctrl-ic/server.h>

int main(void)
{
    printf("Hello kurbits!\n");

    server();
    //seL4_Recv();
    while(1) {}
}