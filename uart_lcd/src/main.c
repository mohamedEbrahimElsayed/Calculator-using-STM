/**
 * *********************************************
 * 
 * 8051 blink demo
 * 
 * PIN: P11
 * 
 * *********************************************
*/

#include "REG52.H"

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

#define EXT0_VECTOR 0  /* 0x03 external interrupt 0 */
#define TIM0_VECTOR 1  /* 0x0b timer 0 */
#define EXT1_VECTOR 2  /* 0x13 external interrupt 1 */
#define TIM1_VECTOR 3  /* 0x1b timer 1 */
#define UART0_VECTOR 4 /* 0x23 serial port 0 */

// LED pin define
sfr LCD_PORT = 0x90;    //P1=KeyPadPort_data pins

 sbit RS=P2^1;
 sbit E=P2^2;

void DELAY(unsigned int time){
    uint16_t I,J;
    for(I=0;I<time;I++)
    for(J=0;J<1275;J++);
}
void initial(void){
    LCD_PORT=0;
    RS=0;
    E=0;
    
}
void LCD_COMM(unsigned char command){
    LCD_PORT=command;
    RS=0;
    E=1;
    DELAY(1);
    E=0;
}
void LCD_INIT(void){
    LCD_COMM(0X38);        //for using 2 lines and 5x7 matrix of lcd
    DELAY(10);
    LCD_COMM(0x0E);         //to turn display on, cursor blinking 
    DELAY(10);
    LCD_COMM(0x01);         //clear screen
    DELAY(10);
}
void LCD_CLEAR(){
    LCD_COMM(0X01);
    DELAY(10);
}
void LCD_DATA(uint8_t disp_data){
    LCD_PORT=disp_data;
    RS=1;
    E=1;
    DELAY(1);
    E=0;
}
void LCD_STRING(char *str){         //dispal string on screen
    int i;
    for(i=0;str[i]!=0;i++){   //send each character of the string till the null
        LCD_DATA(str[i]);
    }
}


// Function to initialize UART with baud rate 2400
void UART_Init() {
    // Set SM0=0, SM1=1 for mode 1 (8-bit UART with variable baud rate)
    // Set BRG value for baud rate 2400
    TMOD = 0x20; // Timer 1, mode 2, 8-bit reload
    TH1 = 0xFD;   // Load TH1 to generate baud rate 2400
    SCON = 0x50; // Mode 1, Receive enable
    TR1 = 1;     // Start Timer 1
}

// Function to transmit a character over UART
void UART_TxChar(uint8_t ch) {
    SBUF = ch;       // Load character into SBUF
    while(TI == 0);  // Wait until transmit is complete
    TI = 0;          // Clear transmit interrupt flag
}

// Function to receive a character over UART
uint8_t UART_RxChar() {
    while(RI == 0);  // Wait until receive is complete
    RI = 0;          // Clear receive interrupt flag
    return SBUF;     // Return received character
}

// Main function




void main(void){
    
	uint8_t indata;
     P2=0;
	initial();
     UART_Init(); // Initialize UART
    LCD_INIT();   
    LCD_STRING("hello\0");
    LCD_CLEAR();
    while (1)
    {
        indata = UART_RxChar(); // Receive character from UART
        if(indata!='c')
        {
             LCD_DATA(indata);
        }
        else
        {
            LCD_CLEAR();
        }
    }
    

}