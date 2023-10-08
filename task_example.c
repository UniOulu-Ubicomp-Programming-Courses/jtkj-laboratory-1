/*
 * task1.c
 *
 *  Created on: 25 Sep 2023
 *      Author: ivan
 */


/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h> //SPECIFIC FOR THE CC2650 SENSOR TAG


/* Board Header files */
#include "Board.h"

// Task needs its own stack memory
#define STACKSIZE 512
Char myTaskStack[STACKSIZE];

// Task implementation
Void myTaskFxn(UArg arg0, UArg arg1) {

   // Taskin ikuinen elämä
   while (1) {
      System_printf("My arguments are %ld ja %ld\n", arg0, arg1);
      System_flush();

      // Politely go to sleep for a moment
      Task_sleep(1000000L / Clock_tickPeriod);
   }
}

int main(void) {

   // Creating task parameters
   Task_Params myTaskParams;
   Task_Handle myTaskHandle;

   // Start device
   Board_initGeneral();

   // Initialize task main parameters
   Task_Params_init(&myTaskParams);
   // Define task stack memory
   myTaskParams.stackSize = STACKSIZE;
   myTaskParams.stack = &myTaskStack;
   // Set task priority
   myTaskParams.priority = 2;
   // Define arguments for the task.
   myTaskParams.arg0 = 127; // Argumentti 1
   myTaskParams.arg1 = 0xFFFF; // Argumentti 2

   // Create task
   myTaskHandle = Task_create((Task_FuncPtr)myTaskFxn, &myTaskParams, NULL);
   if (myTaskHandle == NULL) {
      System_abort("Task create failed");
   }

    // Greetings from console
    System_printf("Creating a task!\n");
    System_flush();

   // Program ready
   BIOS_start();

   return (0);
}
