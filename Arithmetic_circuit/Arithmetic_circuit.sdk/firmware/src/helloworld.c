
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"


int main()
{
    init_platform();

    volatile unsigned int *pointerFifo1 = 0x40000028;
    volatile unsigned int *pointerFifo2 = 0x4000002C;
    int value;

    volatile unsigned int *Settings0 = 0x40000000;
    volatile unsigned int *Settings1 = 0x40000004;
    volatile unsigned int *Settings2 = 0x40000008;
    // ...

    for(int i=0;i<100;i++){
    	xil_printf("Program started %d\r", i);
    	usleep(100000);
    }

    *Settings0=127;

    int LED_VAL = 0;

    while(1){
    	*Settings0 = LED_VAL;
//    	*Settings1 = LED_VAL;
//    	*Settings2 = LED_VAL;
    	LED_VAL++;
    	value=*pointerFifo1;
    	if(value!=-2147483648)
    	{xil_printf("%d\n\r", value);}
    	value=*pointerFifo2;
    	if(value!=-2147483648)
    	{xil_printf("%d\n\r",value);}

    	usleep(100000);
    }

    cleanup_platform();
    return 0;
}
