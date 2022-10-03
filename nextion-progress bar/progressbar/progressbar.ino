#include "Nextion.h"

NexProgressBar j0  = NexProgressBar(0, 3, "j0");
NexButton bup   = NexButton(0, 1, "bup");
NexButton bdown = NexButton(0, 2, "bdown");

NexTouch *nex_listen_list[] = 
{
    &bup,
    &bdown,
    NULL
};

void buttonUpPopCallback(void *ptr)
{
    uint32_t valore = 0;
    dbSerialPrintln("buttonUpPopCallback");

    j0.getValue(&valore);

    valore += 10;
    if (valore >= 100)
    {
        valore = 100;
    }
    
    j0.setValue(valore);
}

void buttonDownPopCallback(void *ptr)
{
    uint32_t valore = 0;
    dbSerialPrintln("buttonDownPopCallback");

    j0.getValue(&valore);

    if (valore >= 10)
    {
        valore -= 10;
    }
    
    j0.setValue(valore);
}

void setup(void)
{
    nexInit();
    bup.attachPop(buttonUpPopCallback);
    bdown.attachPop(buttonDownPopCallback);
    
}

void loop(void)
{
    nexLoop(nex_listen_list);
}
