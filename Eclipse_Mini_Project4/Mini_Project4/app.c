
#include"ultrasonic.h"
#include "lcd.h"
#include <avr/io.h>



int main(void)
{
	uint16 distance=0;
	SREG|=(1<<7);

	Ultrasonic_init();
	LCD_init();


	LCD_displayString("Distance=    cm");


	while(1)
	{

		distance= Ultrasonic_readDistance();
		LCD_moveCursor(0,10);

		if(distance >=100 )
		{
			LCD_integerToString(distance);
		}
		else
		{
			LCD_integerToString(distance);
			LCD_displayCharacter(' ');
		}

	}

}
