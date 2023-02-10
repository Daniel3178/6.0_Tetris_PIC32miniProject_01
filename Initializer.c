#include "pic32max.h"
#include "TetrisGeneral.h"

unsigned char OLED_DisplayBuffer[512];

#pragma region DISPLAY_INITIALIZER_STUFF

void OledPutBuffer(int cb, unsigned char* rgbTx)
{
	int ib;
	unsigned char bTmp;
	/* Write/Read the data
	*/
	for (ib = 0; ib < cb; ib++) {
		/* Wait for transmitter to be ready
		*/
		//SPI2STATbits.SPITBE
		while ((SPI2STAT & 0x08)== 0);
		/* Write the next transmit byte.
		*/
		SPI2BUF = *rgbTx++;
		/* Wait for receive byte.
		*/
		//SPI2STATbits.SPIRBF
		while ((SPI2STAT & 0x1)  == 0);
		bTmp = SPI2BUF;
	}
}
unsigned char Spi2PutByte(unsigned char bVal)
{
	unsigned char bRx;
	/* Wait for transmitter to be ready
	*/
	//SPI2STATbits.SPITBE
	while ((SPI2STAT & 0x08) == 0);
	/* Write the next transmit byte.
	*/
	SPI2BUF = bVal;
	/* Wait for receive byte.
	*/
	//SPI2STATbits.SPIRBF
	while ((SPI2STAT & 0x1) == 0);
	/* Put the received byte in the buffer.
	*/
	bRx = SPI2BUF;
	return bRx;
}
void OledHostInit()
{
	unsigned int tcfg;
	/* Initialize SPI port 2.
	*/
	SPI2CON = 0;
	SPI2BRG = 15; //8Mhz, with 80Mhz PB clock

	SPI2STATCLR = PIC32_SPISTAT_SPIROV; //spirov is the bit index 6 that should be turned off source: family data sheet p.61
	SPI2CONSET = PIC32_SPICON_CKP;		//ckp is is the bit index 6 that should be turned on source: family data sheet p.61		  
	SPI2CONSET = PIC32_SPICON_MSTEN;	//msten is the bit index 5 that should be turned on source: family data sheet p.61		  
	SPI2CONSET = PIC32_SPICON_ON;		//on is the bit index 15 that should be turned on source: family data sheet p.61	      
/* Make pins RF4, RF5, and RF6 be outputs.
*/
/*RF6 = bitVddCtrl, R5= bitVbatCtrl, R4 = bitDataCmd */
//PORTSetBits(IOPORT_F, bitVddCtrl | bitVbatCtrl | bitDataCmd);                           
//PORTSetPinsDigitalOut(prtDataCmd, bitDataCmd); //Data/Command# select
//PORTSetPinsDigitalOut(prtVddCtrl, bitVddCtrl); //VDD power control (1=off)
//PORTSetPinsDigitalOut(prtVbatCtrl, bitVbatCtrl); //VBAT power control (1=off)
	TRISFCLR = 0X70; //RF4, RF5, RF6 are bits index 4,5,6 respectively, tris of the corresponding port should be turned off for outputs
	PORTFSET = 0X70; //To set the above pins as outputes. Source: family data sheet p.74

	/* Make the RG9 pin be an output. On the Basic I/O Shield, this pin
	** is tied to reset.
	*/
	TRISGCLR = 0X200; //RG9 is the pin index 9 and should be turned of to make it as an output. Source: family data sheet p.74
	PORTGSET = 0X200;
}
void OledDspInit()
{
	/* We're going to be sending commands, so clear the Data/Cmd bit
	*/
	PORTFCLR = 0x10; //Rf4 = data/cmd bit
	/* Start by turning VDD on and wait a while for the power to come up.
	chipKIT� Basic I/O Shield� Reference Manual
	Copyright Digilent, Inc. All rights reserved.
	Other product and company names mentioned may be trademarks of their respective owners. Page 11 of 13
	*/
	quickTimer(10);
	PORTFCLR = 0x40; // 0 = on 
	quickTimer(1000000);
	//1ms delay
	/* Display off command
	*/
	Spi2PutByte(0xAE);
	/* Bring Reset low and then high
	*/
	PORTGCLR = 0x200;
	quickTimer(10);
	//1ms delay
	PORTGSET = 0x200;
	/* Send the Set Charge Pump and Set Pre-Charge Period commands
	*/
	quickTimer(10);

	Spi2PutByte(0x8D);
	Spi2PutByte(0x14);
	Spi2PutByte(0xD9);
	Spi2PutByte(0xF1);
	/* Turn on VCC and wait 100ms
	*/
	PORTFCLR = 0X20; //RF6 = VDD
	quickTimer(10000000);
	//100 ms delay
	/* Send the commands to invert the display. This puts the display origin
	** in the upper left corner.
	*/
	Spi2PutByte(0xA1); //remap columns
	Spi2PutByte(0xC8); //remap the rows
	/* Send the commands to select sequential COM configuration. This makes the
	** display memory non-interleaved.
	*/
	Spi2PutByte(0xDA); //set COM configuration command
	Spi2PutByte(0x20); //sequential COM, left/right remap enabled
	/* Send Display On command
	*/
	Spi2PutByte(0xAF);
}
void OledUpdate()
{
	int ipag;
	int icol;
	unsigned char* pb;
	pb = OLED_DisplayBuffer;

	for (ipag = 0; ipag < 4; ipag++) {
		PORTFCLR = 0x10; //Rf4 = Data/Cmd
		//PORTClearBits(prtDataCmd, bitDataCmd);
		/* Set the page address
		*/
		Spi2PutByte(0x22); //Set page command
		Spi2PutByte(ipag); //page number
		/* Start at the left column
		*/
		Spi2PutByte(0x00); //set low nybble of column
		Spi2PutByte(0x10); //set high nybble of column
		PORTFSET = 0X10; //RF4 = Data/Cmd
		//PORTSetBits(prtDataCmd, bitDataCmd);
		/* Copy this memory page of display data.
		*/
		OledPutBuffer(128, pb);
		pb += 128;
	}
}

#pragma endregion

#pragma region IO_INITIALIZER_STUFF

void ioInitializer() {
	TRISECLR = 0xff; // the led lamps 0 - 7
	PORTECLR = 0x000000ff;
	PORTE = 0;
	TRISDSET = 0xfe0; //switches and btns 
	TRISFSET = 0x2; //btn 1 
}

int getws(void) { //returns the state of swich 1 through 4 where the lsb represents state of switch 1
	int result = ((((PORTD >> 8) & 0X8) | ((PORTD >> 8) & 0x4) | ((PORTD >> 8) & 0x2) | ((PORTD >> 8) & 0X1)) & 0Xf);
	return result;
}

int getbtns(void) { //return the state of btn 1 through 4 where the lsb represents state of btn 1
	int result = ((((PORTD >> 5) & 0X8) | ((PORTD >> 5) & 0X4) | ((PORTD >> 5) & 0X2) | ((PORTF >> 1) & 0X1)) & 0Xf);
	return result;
}
#pragma endregion

#pragma region TIMER_INITIALIZER_STUFF
void timerInitializer() {
	//Initialize Timer2
	T2CONSET = 0x70; //0111 0000, Sets prescale to 1:256
	IFSCLR(0) = 0x100;//0001 0000 0000
	PR2 = 7812; //40 FPS
	TMR2 = 0;
	T2CONSET = 0x08000; // 1000 0000 0000 0000, Start timer

	IPCSET(2) = 0x1f; //0001 1111 - Bit 4:2 Priority, Bit 1:0 Subpriority.
	IECSET(0) = 0x100; // 0001 0000 0000 - Bit 8 enable interupts from Timer2

	//enable_interrupts();

	IPCSET(2) = 0x1f;
	IECSET(0) = 0x100;
}

void quickTimer(int timeout) {
	int i;
	for (i = 0; i < timeout; i++) {
		i++;
	}
}
#pragma endregion

#pragma region UNO32_INITIALIZER

void uno32Initializer() {

	ioInitializer();
	//Set the seed for the random
	//srand(getSwitches());

	//Setup display
	OledHostInit();
	OledDspInit();

	timerInitializer();

}

//void user_isr() {
//	OledUpdate();
//	IFSCLR(0) = 0x100;//0001 0000 0000
//	return;
//}

#pragma endregion

#pragma region FIELD_INITIALIZER

void fieldInitializer() {
	unsigned char i = 0;
	unsigned char j = 0;

	for (i = 0; i < 32; i++) {
		for (j = 0; j < 128; j++) {
			if (i == 0 || i == 31 || j == 0 || j == 127) {
				tetrisField[i][j] = 1;
			}
			else {
				tetrisField[i][j] = 0;
			}
		}
	}
}
 void clearDisplay()
 {
   int i;
   for(i = 0; i < 512; i++)
     OLED_DisplayBuffer[i] = 0;
 }
#pragma endregion


// /*function to print letters/words/digit etc*/
