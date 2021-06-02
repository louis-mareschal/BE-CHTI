#include "DriverJeuLaser.h"
#include "GestionSon.h"


int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();

// configuration du Timer 4 en d�bordement 100ms
Timer_1234_Init_ff( TIM4, 6552); // 72 000 000 * 91 * 10^-6

// Activation des interruptions issues du Timer 4
// Association de la fonction � ex�cuter lors de l'interruption : timer_callback
// cette fonction (si �crite en ASM) doit �tre conforme � l'AAPCS
		
Active_IT_Debordement_Timer( TIM4, 2, CallbackSon);	

// Configuration de la PWM 
PWM_Init_ff( TIM3, 3,720); // Periode ticks � 720 donc Tpwm = Tclk * 720 = (1/72 000 000 ) * 720 = 10^-6 s = 1 �s

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
