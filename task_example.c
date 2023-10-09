/*
 * task1.c
 *
 *  Created on: 25 Sep 2023
 *      Author: ivan
 */




// Taski tarvitsee oman sisäisen pinomuistin
#define STACKSIZE 512
Char myTaskStack[STACKSIZE];

enum state {IDLE, READY};
enum state program_state= IDLE;
// Taskin toteutusfunktio
Void myTaskFxn(UArg arg0, UArg arg1) {

   // Taskin ikuinen elämä
   while (1) {
      System_printf("This is task %ld\n", arg0);
      System_flush();

      // Kohteliaasti nukkumaan hetkeksi
      Task_sleep(1000000L / Clock_tickPeriod);
   }
}

int main(void) {

   // Taskeihin liittyviä tietorakenteita
   Task_Params myTaskParams;
   Task_Handle myTaskHandle;
   Task_Params myTask2Params;
   Task_Handle myTask2Handle;

   // Laitteen alustus
   Board_initGeneral();

   // Alustetaan taskin suoritusparametrit
   Task_Params_init(&myTaskParams);
   Task_Params_init(&myTask2Params);
   // Osoitetaan taskille sen pinomuisti
   myTaskParams.stackSize = STACKSIZE;
   myTaskParams.stack = &myTaskStack;
   myTask2Params.stackSize = STACKSIZE;
   myTask2Params.stack = &myTask2Stack;
   // Asetetaan taskin prioriteetti
   myTaskParams.priority = 2;
   myTask2Params.priority = 1;
   myTaskParams.arg0 = 1;
   myTask2Params.arg0 = 2;


   // Luodaan taski
   myTaskHandle = Task_create((Task_FuncPtr)myTaskFxn, &myTaskParams, NULL);
   myTask2Handle = Task_create((Task_FuncPtr)myTaskFxn, &myTask2Params, NULL);
   if (myTaskHandle == NULL || myTask2Handle == NULL) {
      System_abort("Task create failed");
   }

    // Terveisiä konsolille
    System_printfss("Creating task!\n");
    System_flush();

   // Ohjelma käynnistyy
   BIOS_start();

   return (0);
