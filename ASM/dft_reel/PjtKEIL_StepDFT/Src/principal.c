#include "DriverJeuLaser.h"
#include "Affichage_Valise.h"
int DFT_ModuleAuCarre( short int * signal, int k) ;
short int dma_buf[64];
int tab[64];
extern short int LeSignal;

void callback () {
	
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	int score[6] = {0,0,0,0,0,0};
	int seuil =  0x1400000;
	for (int k = 0; k<64; k++) {
		tab[k] = DFT_ModuleAuCarre( dma_buf, k) ;
		if (tab[k] > seuil) {
			switch (k) {
				case 17:
					score[0] ++;
					break;
				case 18:
					score[1] ++;
					break;
				case 19:
					score[2] ++;
					break;
				case 20:
					score[3] ++;
					break;
				case 21:
					score[4] ++;
					break;
				case 22:
					score[5] ++;
					break;
			}
		}
	}
}	
	
int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();
	// configuration de Port1.2 (PA2) en entrée GBF
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG); // ??

		
	 Systick_Period_ff(360000);
	 Systick_Prio_IT( 3, callback );
		SysTick_On ;
		SysTick_Enable_IT ;
	
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );

	// préparation des LEDs
	for (int i= 0; i < 4; i++){
		Prepare_Afficheur(i, 0);
	}

	//============================================================================	
	
	while	(1) {}
}

