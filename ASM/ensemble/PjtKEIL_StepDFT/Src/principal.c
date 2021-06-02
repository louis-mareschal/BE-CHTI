#include "DriverJeuLaser.h"
#include "Affichage_Valise.h"
#include "GestionSon.h"
#include <stdlib.h>
#include <time.h>  

int DFT_ModuleAuCarre( short int * signal, int k) ;
short int dma_buf[64];
int tab[64];
int score[6] = {0,0,0,0,0,0};
int compteur[6] = {0,0,0,0,0,0};
extern short int LeSignal;
int capteur = 2;

void callback () {
	
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	int seuil =  0xfc;
	for (int k = 0; k<64; k++) {
		tab[k] = DFT_ModuleAuCarre( dma_buf, k) ;
		if (tab[k] > seuil) {
			switch (k) {
				case 17:
					compteur[0] ++;
					break;
				case 18:
					compteur[1] ++;
					break;
				case 19:
					compteur[2] ++;
					break;
				case 20:
					compteur[3] ++;
					break;
				case 21:
					compteur[4] ++;
					break;
				case 22:
					compteur[5] ++;
					break;
			}
		} else {
			switch (k) {
				case 17:
					compteur[0] = 0;
					break;
				case 18:
					compteur[1] = 0;
					break;
				case 19:
					compteur[2] = 0;
					break;
				case 20:
					compteur[3] = 0;
					break;
				case 21:
					compteur[4] = 0;
					break;
				case 22:
					compteur[5] = 0;
					break;
		}
	}
		
}
	for (int k = 0; k < 4; k++) {
		if (compteur[k] == 12) {
			score[k]++;
			// Si une cible est touchée on change
			// On choisit la cible 1 pour test
			
			switch(capteur) {
				case 1:
					Prepare_Clear_LED(LED_Cible_1);
					break;
				case 2:
					Prepare_Clear_LED(LED_Cible_2);
					break;
				case 3:
					Prepare_Clear_LED(LED_Cible_3);
					break;
				case 4:
					Prepare_Clear_LED(LED_Cible_4);
					break;
			}
			srand(rand()); 
			capteur = rand()%4 + 1;
			
			Choix_Capteur(capteur);
			// allumer la bonne led
			switch(capteur) {
				case 1:
					Prepare_Set_LED(LED_Cible_1);
					break;
				case 2:
					Prepare_Set_LED(LED_Cible_2);
					break;
				case 3:
					Prepare_Set_LED(LED_Cible_3);
					break;
				case 4:
					Prepare_Set_LED(LED_Cible_4);
					break;
			}
			 
			Prepare_Afficheur(k + 1, score[k]);
			StartSon() ;
		}	
	}

	
	
	Mise_A_Jour_Afficheurs_LED();
}
	
int main(void)
{
	
	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================
	// SIGNAL //
	
			// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
			CLOCK_Configure();
			// configuration de Port1.2 (PA2) en entrée GBF
			GPIO_Configure(GPIOA, 3, INPUT, ANALOG); // ??
			Systick_Period_ff(360000);
			Systick_Prio_IT( 9, callback );
			SysTick_On ;
			SysTick_Enable_IT ;
			Init_TimingADC_ActiveADC_ff( ADC1, 72 );
			Single_Channel_ADC( ADC1, 2 );
			Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
			Init_ADC1_DMA1( 0, dma_buf );
	
	
	// SON //
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

	// Affichage //
			Init_Affichage();
			// On choisit la cible 2 pour test
			Choix_Capteur(2);
			// allumer la bonne led
			 Prepare_Set_LED(LED_Cible_2);
			 // Initialiser les scores
			 for (int k = 0; k < 3; k++) {
					Prepare_Afficheur(k + 1, score[k]);
			 }
				Mise_A_Jour_Afficheurs_LED();

	//============================================================================	
	
	while	(1) {
	}
}

