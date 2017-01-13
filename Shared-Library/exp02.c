#include <wiringPi.h>

#ifdef __cplusplus
extern "C"
{
#endif
	void mygpio_init (char PIN, char MODE);
	void mygpio_write (char PIN, char state);
#ifdef __cplusplus
}
#endif

/*
#define	INPUT			 	0
#define	OUTPUT			 	1
#define	PWM_OUTPUT		 	2
#define	GPIO_CLOCK		 	3
#define	SOFT_PWM_OUTPUT		4
#define	SOFT_TONE_OUTPUT	5
#define	PWM_TONE_OUTPUT		6
 */
void mygpio_init (char PIN, char MODE)
{
  wiringPiSetup () ;
  pinMode (PIN, MODE) ;
}

void mygpio_write (char PIN, char state)
{
    digitalWrite (PIN, state);
}
