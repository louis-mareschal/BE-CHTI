#include "DriverJeuLaser.h"

int DFT_ModuleAuCarre( short int * Signal64ech, int k) ;
int tab[64];
extern short int LeSignal;
int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();


		
		

	//============================================================================	
	for (int k = 0; k<64; k++) {
		tab[k] = DFT_ModuleAuCarre( &LeSignal, k);
		
	}
	while	(1) {}
}

