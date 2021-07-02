#include "bcm2835-armctrl-ic/server.h"

#include <stdio.h> //printf
#include <sel4platsupport/io.h> //printf

void server() {
  printf("Hello server!\n");
  while(1);
}