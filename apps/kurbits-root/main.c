#include <sel4/sel4.h>
#include <stdio.h> //printf
#include <sel4platsupport/bootinfo.h>
#include <sel4platsupport/io.h> //printf
#include <bcm2835-armctrl-ic/server.h>

char bcm2835_armctrl_ic_server_stack_buffer[4096 * 2];

int main(void)
{
    printf("Hello kurbits!\n");

    seL4_BootInfo *info = platsupport_get_bootinfo();

    seL4_Word server_untyped_bits = 1 + MAX(seL4_TCBBits, 2 + seL4_SlotBits);
    seL4_CPtr slot;
    for (slot = info->untyped.start; slot != info->untyped.end; slot++) {
        seL4_UntypedDesc *desc = &info->untypedList[slot - info->untyped.start];
        if (!desc->isDevice && desc->sizeBits > server_untyped_bits) break;
    }

    seL4_CPtr bcm2835_armctrl_ic_server_TCB = info->empty.start++;
    seL4_CPtr bcm2835_armctrl_ic_server_SC = info->empty.start++;
    seL4_CPtr bcm2835_armctrl_ic_server_CSpace = info->empty.start++;

    seL4_Untyped_Retype(slot, // the untyped capability to retype
        seL4_TCBObject, // type
        seL4_TCBBits,  //size
        seL4_CapInitThreadCNode, // root
        0, // node_index
        0, // node_depth
        bcm2835_armctrl_ic_server_TCB, // node_offset
        1 // num_caps
    );

    seL4_Untyped_Retype(slot, // the untyped capability to retype
        seL4_SchedContextObject,// type
        seL4_MinSchedContextBits,  //size
        seL4_CapInitThreadCNode, // root
        0, // node_index
        0, // node_depth
        bcm2835_armctrl_ic_server_SC, // node_offset
        1 // num_caps
    );

    seL4_TCB_Configure(
        bcm2835_armctrl_ic_server_TCB, // _service, TCB we're acting on
        //seL4_CapNull, // fault_ep, enpoint notified if thread faults
        seL4_CapInitThreadCNode, // cspace_root, root cnode of the TCB
        0, // cspace_root_data, optional guard
        seL4_CapInitThreadVSpace, // vspace_root
        0, // vspace_root_data
        (seL4_Word)&info->ipcBuffer[1], // buffer, thread IPC buffer
        seL4_CapInitThreadIPCBuffer//memoryServiceIPCPage // bufferFrame, page cap for buffer frame
    );

    seL4_SchedControl_ConfigureFlags(
        info->schedcontrol.start,
        bcm2835_armctrl_ic_server_SC,
        20000,
        20000,
        0,
        0,
        0
    );

    seL4_SchedContext_Bind(bcm2835_armctrl_ic_server_SC, bcm2835_armctrl_ic_server_TCB);

    seL4_TCB_SetTLSBase(bcm2835_armctrl_ic_server_TCB, (seL4_Word) &bcm2835_armctrl_ic_server_stack_buffer[4096]);
    seL4_UserContext regs = {0};
    seL4_TCB_ReadRegisters(bcm2835_armctrl_ic_server_TCB, 0, 0, sizeof(regs)/sizeof(seL4_Word), &regs);
    regs.pc = (seL4_Word) server;
    regs.sp = (seL4_Word) &bcm2835_armctrl_ic_server_stack_buffer[4096];

    seL4_TCB_WriteRegisters(bcm2835_armctrl_ic_server_TCB, 1, 0, sizeof(regs)/sizeof(seL4_Word), &regs);
  	seL4_TCB_SetPriority(bcm2835_armctrl_ic_server_TCB, seL4_CapInitThreadTCB, 255);

    while(1) {}
}