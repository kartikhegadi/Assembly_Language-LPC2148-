#include <lpc214x.h>

void uart_interrupt(void)__irq ;
unsigned char temp , temp1 = 0x00 ;
unsigned char rx_flag = 0 , tx_flag = 0,*ptr ;
unsigned char arr[]="HELLO HUBLI\r";
unsigned int i;

int main(void)
{
	PINSEL0=0X0000005;  				//select TXD0 and RXD0 lines		   
	U0LCR = 0X00000083;					//enable baud rate divisor loading and
	U0DLM = 0X00;          				//select the data format
  U0DLL = 0x13;      					//select baud rate 9600 bps
  U0LCR = 0X00000003;
	U0IER = 0X03;	   					//select Transmit and Recieve interrupt

  VICVectAddr0 = (unsigned long)uart_interrupt;	//UART 0 INTERRUPT 
  VICVectCntl0 = 0x20|6;  			// Assign the VIC channel uart-0 to interrupt priority 0
	VICIntEnable = 0x00000040;     		// Enable the uart-0 interrupt
		                
  while(1)
  {
			ptr=arr;
			while ( *ptr != '\0')
		{ 
  
			temp1 =	*ptr++;		
		  U0THR = temp1 ;

      while(tx_flag == 0x00); 		//wait for transmit flag to set 
		  tx_flag = 0x00;         		//clear the flag
		for(i=0;i<=300;i++);	
    }
		for(i=0;i<=30000;i++);		
}
}		

void uart_interrupt(void)__irq
{
	temp = U0IIR;
   	temp = temp & 0x06;

    if(temp  == 0x02)
	{
    	tx_flag = 0xff;
     	VICVectAddr=0; 
	}

}

