#include "Nextion.h"

//Dichiara l'oggetto Dual State Button [page id:0,component id:1, component name: "bt0"]. 
NexDSButton button = NexDSButton(0, 1, "button");

char buffer[100] = {0};

// Registra nell'elenco degli eventi touch
NexTouch *nex_listen_list[] = 
{
    &button,
    NULL
};


void setup(void)
{    
    pinMode (13, OUTPUT);
    nexInit();            //Inizializzazione del seriale a 9600
    digitalWrite(13, LOW);

   
}

void loop(void)
{   
    // Richiama la funzione Pop Callbak e registra l'evento
    button.attachPop(buttonPopCallback, &button);

    nexLoop(nex_listen_list);
}


void buttonPopCallback(void *ptr)
{
    uint32_t dual_state;
    NexDSButton *btn = (NexDSButton *)ptr;
    
    dbSerialPrintln("b0PopCallback");
    dbSerialPrint("ptr=");
    dbSerialPrintln((uint32_t)ptr); 
    memset(buffer, 0, sizeof(buffer));

    // Si ottiene lo stato del bottone e accende o spegne un LED
    button.getValue(&dual_state);
    if(dual_state) 
    {
        digitalWrite(13, HIGH);
    }
    else
    {
       digitalWrite(13, LOW);
    }
}
