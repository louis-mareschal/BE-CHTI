#include "DriverJeuLaser.h"

int DFT_ModuleAuCarre( short int * Signal64ech, int k) ;
int tab[64];
extern short int LeSignal;
int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
	CLOCK_Configure();


		
		

	//============================================================================	
	for (int k = 0; k<64; k++) {
		tab[k] = DFT_ModuleAuCarre( &LeSignal, k);
		
	}
	while	(1) {}
}

