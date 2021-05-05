#include "DriverJeuLaser.h"
#include "GestionSon.h"


int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

// configuration du Timer 4 en débordement 100ms
Timer_1234_Init_ff( TIM4, 6552); // 72 000 000 * 91 * 10^-6

// Activation des interruptions issues du Timer 4
// Association de la fonction à exécuter lors de l'interruption : timer_callback
// cette fonction (si écrite en ASM) doit être conforme à l'AAPCS
		
Active_IT_Debordement_Timer( TIM4, 2, CallbackSon);	

// Configuration de la PWM 
PWM_Init_ff( TIM3, 3,720); // Periode ticks à 720 donc Tpwm = Tclk * 720 = (1/72 000 000 ) * 720 = 10^-6 s = 1 µs

// configuration de PortB.0 pour la PWM
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

	
// configuration de PortB.1 (PB1) en sortie push-pull
GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	
	

//============================================================================	
	
	
while	(1)
	{
		for( long int i = 0 ; i < 10000000 ; i++) {
			
		}
		StartSon() ;
	}
}
