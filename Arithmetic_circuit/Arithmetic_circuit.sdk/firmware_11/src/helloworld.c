
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
#define WAIT_US 1


#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include <stdlib.h>
#include "data.h"

int read_fpga();
int read_and_write_FPGA();
void print_bits(int posit);


int main(){
    init_platform();

	for(int i=0;i<100;i++){
		xil_printf("Program started %d\r", i);
		usleep(50000);
	}

	xil_printf("START\n\r");
    read_and_write_FPGA();
    cleanup_platform();
    return 0;
}

//
//int main()
//{
//    init_platform();
//
//    volatile unsigned int *pointerFifo1 = 0x40000028;
//    volatile unsigned int *pointerFifo2 = 0x4000002C;
//    int value;
//
//    volatile unsigned int *Settings0 = 0x40000000;
//    volatile unsigned int *Settings1 = 0x40000004;
//    volatile unsigned int *Settings2 = 0x40000008;
//    // ...
//

//
//    *Settings0=127;
//
//    int LED_VAL = 0;
//
//    int one = 0;
//    int two = 0;
//    for(int i=0;i<32;i++){
//    	one = (one << 2) | (2);
//    	two = (two << 2) | (1);
//    }
//
//    while(1){
//    	if(LED_VAL % 2 == 0){
//    		*Settings0 = one;
//    	}else{
//    		*Settings0 = two;
//    	}
//
//
//    	LED_VAL++;
//    	value=*pointerFifo1;
//    	if(value!=-2147483648)
//    	{xil_printf("%d\n\r", value);}
//    	value=*pointerFifo2;
//    	if(value!=-2147483648)
//    	{xil_printf("%d\n\r",value);}
//
//    	usleep(100000);
//    }
//
//    cleanup_platform();
//    return 0;
//}


int read_and_write_FPGA(){

    // Write to FPGA
    volatile unsigned int *Settings0 = 0x40000000;

    // SPN info
    int input_width = 34 / 2;

    int bit=0;
    int bitstream=0;
    int j=0;

    for(int n_data=0;n_data<50000;n_data++){
//    	xil_printf("Pushing data %d\n\r", n_data);
    	bitstream = 0;

		for(int i=0;i<input_width;i++){
			bit = data[n_data][input_width-i-1];
			for(int k=0;k<2;k++){
				bitstream = bitstream << 1 | bit;
				j++;
				static int tmp = 0;
				if(j==17){
					for(int v=0;v<17;v++){
						tmp = (tmp << 1) | (bitstream % 2);
						bitstream = bitstream >> 1;
					}
//					print_bits(tmp);
//					xil_printf("Sent %d %d\n\r", n_data,k);
					*Settings0 = tmp;
					tmp = 0;
					bitstream = 0; // reset
					j=0;
				}
				bit = bit==0 ? 1 : 0;
				usleep(WAIT_US);
				read_fpga();
			}
		}
    }

    while(1){
    	read_fpga();
    	usleep(WAIT_US);
    }

    return 0;
}

//     for(int n_data=0;n_data<10;n_data++){
// //    	xil_printf("Pushing data %d\n\r", n_data);
//     	i=0;
//     	j=0;
//     	bitstream = 0;

// 		while(i < input_width){
// 			bit = data[n_data][input_width-i-1]==0 ? 1 : 0;
// 			for(int k=0;k<2;k++){
// 				bit = bit==0 ? 1 : 0; // inverse bit, start with negative lit

// 				if(j==17){
// 					xil_printf("Pushed bits : ");
// 					print_bits(bitstream);
// 					*Settings0 = bitstream;
// 					usleep(WAIT_US);

// 					bitstream = 0;
// 					j=0;
// 				}

// 				bitstream = (bitstream << 1) | bit;

// 				j++;
// 				read_fpga();
// 			}
// 			i++;
// 		}
// 		xil_printf("Pushed bits : ");
// 		print_bits(bitstream);
// 		*Settings0 = bitstream;
// 		usleep(WAIT_US);
// 		bitstream = 0;
//     }


int read_fpga(){
	int output;
	int value;

    // Read from FPGA on fifo 1
    // Acknowledge read on fifo 2
    volatile unsigned int *pointerFifo1 = 0x40000028;
    volatile unsigned int *pointerFifo2 = 0x4000002C;


	output=*pointerFifo1;
	if(output!=-2147483648){
//		xil_printf("%d\n\r", output);
		print_bits(output);
	}
	value=*pointerFifo2;
	if(value!=-2147483648){
		xil_printf("%d\n\r",value);
	}

	if(output == -2147483648){
		return -1;
	}

	return output;
}

void print_bits(int value){
    int tmp = 0;
    for(int i=0;i<16;i++){
        tmp = (tmp << 1) | (value % 2);
        value = value >> 1;
    }

    for(int i=0;i<16;i++){
        xil_printf("%d", tmp % 2);
        tmp = tmp >> 1;
    }
    xil_printf("\r");
}


