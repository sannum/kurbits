#pragma once

#include <sel4/sel4.h>

struct bcm2835_armctrl_ic_server {
  seL4_CPtr parent_ep;
  seL4_Untyped untyped;
  seL4_CPtr empty;
};

void server();