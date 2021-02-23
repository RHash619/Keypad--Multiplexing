
#define F_CPU 16000000UL  // 

#include <avr/io.h>
#include <util/delay.h>

void USART_init(void);
void USART_Tx( unsigned char data);
#define BAUD 9600								 
#define BAUDRATE (((F_CPU / (BAUD * 16UL))) - 1) 

void keypadScan(unsigned char keypad[4][4]);

unsigned char keypad[4][4] = {	{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}  };

int main(void)
{
	USART_init();
	
	DDRD |= (1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);        //set row of PD4,PD5,PD6,PD7 as output
	DDRB &= ~(1<<DDB0)& ~(1<<DDB1)& ~(1<<DDB2)& ~(1<<DDB3); //set column of PB0,PB1,PB2,PB3 as input
	
	while(1)
	{
		keypadScan(keypad);
	}
}

void keypadScan(unsigned char keypad[4][4])
{
	uint8_t i, j;
	
	PORTD |= (1<<4|1<<5|1<<6|1>>7);		
	for(i=1;i<5;i++)
	{
		PORTD &= ~(1<<i);				 
		for(j=1;i<5;j++)
		{
			if(!(PINB & (1<<j)))		
			{
				USART_Tx(keypad[i][j]);  
			}
		}
	}
}

void USART_init(void){
	
	UBRR0H = (BAUDRATE>>8);
	UBRR0L = (BAUDRATE);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01)|(0<<USBS0);
}

void USART_Tx(unsigned char data){
	
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
}
