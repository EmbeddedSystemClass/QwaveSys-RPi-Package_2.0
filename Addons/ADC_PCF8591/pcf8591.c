#include <wiringPi.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pcf8591.h>

int pcf8591init( void );
int pcf8591_AI(int pin);
void pcf8591_AO( int dac );

double volts (int value)
{
        return value * 3.3 /255;
}

int pcf8591init( void ) {
	if (wiringPiSetup() == -1)
                return 0;

        pcf8591Setup(80, 0x48);

        pinMode (80, INPUT);
        pinMode (81, INPUT);
        pinMode (82, INPUT);
	pinMode (83, INPUT);

	return 1;
}

int pcf8591_AI(int pin) {
	return analogRead(80+pin);
}

void pcf8591_AO( int dac ) {
	analogWrite (80, dac);
}

int main (void)
{
        if (!pcf8591init())
                exit (1);

	float v = 0;
        for(;;)
        {
		v += 0.1;
		pcf8591_AO( v/3.3*255 );
		if(v >= 3.3) v = 0;
                printf ("%f   %f  %f  %f\n", volts(pcf8591_AI(0)), volts(pcf8591_AI(1)), volts(pcf8591_AI(2)),volts(pcf8591_AI(3)));
                delay(1000);
        }
        return 0;
}

